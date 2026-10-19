// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (c) 2026 Noethric. NoeMixerr MCP integration.
// The original LMMS source and authors are credited separately.
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDir>
#include <QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QSaveFile>
#include <QTextStream>
#include <QUuid>
#include <cstdio>
#include <stdexcept>

namespace {
struct Pending {
    QString canonicalPath;
    QByteArray fingerprint;
    QString operation;
    QJsonObject args;
};
QString workspace;
bool writesEnabled = false;
QHash<QString, Pending> pending;

QString err(const QString& message) { throw std::runtime_error(message.toStdString()); }
QJsonObject object(const QByteArray& value) {
    QJsonParseError e{};
    auto result = QJsonDocument::fromJson(value, &e);
    if (e.error != QJsonParseError::NoError || !result.isObject()) {
        err("Invalid JSON object");
    }
    return result.object();
}
QJsonObject objectLiteral(const char* data) { return object(QByteArray(data)); }
QJsonObject textResult(const QJsonObject& v) {
    return QJsonObject{
        {"content", QJsonArray{QJsonObject{{"type","text"}, {"text", QString::fromUtf8(QJsonDocument(v).toJson(QJsonDocument::Compact))}}}},
        {"isError", false}
    };
}
QJsonObject toolError(const QString& message) {
    return QJsonObject{
        {"content", QJsonArray{QJsonObject{{"type","text"}, {"text", message}}}},
        {"isError", true}
    };
}
QString checkedPath(const QJsonObject& args) {
    const auto relative = args.value("path").toString();
    if (relative.isEmpty()) err("Missing project path");
    QFileInfo info(relative);
    const QString resolved = info.isAbsolute()
        ? info.canonicalFilePath()
        : QFileInfo(QDir(workspace).filePath(relative)).canonicalFilePath();
    if (resolved.isEmpty() || (!resolved.endsWith(".mmp", Qt::CaseInsensitive))) {
        err("Expected existing .mmp project file");
    }
    if (!resolved.startsWith(workspace + QDir::separator())) {
        err("Project must be inside NOEMIXERR_WORKSPACE");
    }
    if (!QFileInfo(resolved).isFile()) err("Not a regular file");
    return resolved;
}
QByteArray readBounded(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) err("Cannot read project");
    if (file.size() < 1 || file.size() > 32 * 1024 * 1024) err("Project file size exceeds limit");
    return file.readAll();
}
QDomDocument parseProject(const QByteArray& bytes) {
    QDomDocument doc;
    QString message;
    int line = 0, column = 0;
    if (!doc.setContent(bytes, &message, &line, &column)) {
        err(QString("Invalid XML at %1:%2: %3").arg(line).arg(column).arg(message));
    }
    if (doc.documentElement().tagName() != "lmms-project"
        && doc.documentElement().tagName() != "noemixerr-project") {
        err("Unsupported project root");
    }
    return doc;
}
QJsonObject inspect(const QJsonObject& args) {
    const QString path = checkedPath(args);
    const QDomDocument doc = parseProject(readBounded(path));
    const QDomElement root = doc.documentElement();
    const QDomElement head = root.firstChildElement("head");
    if (head.isNull()) err("Missing song head");
    return QJsonObject{
        {"path", QFileInfo(path).fileName()},
        {"root", root.tagName()},
        {"bpm", head.attribute("bpm").toDouble()},
        {"track_elements", doc.elementsByTagName("track").count()},
        {"notes", doc.elementsByTagName("note").count()},
        {"editable_patterns", doc.elementsByTagName("pattern").count()}
    };
}
void validEdit(const QJsonObject& a) {
    const QString op = a.value("operation").toString();
    if (op == "set_tempo") {
        const auto bpm = a.value("bpm");
        if (!bpm.isDouble() || bpm.toDouble() < 20 || bpm.toDouble() > 400) err("BPM must be 20..400");
    } else if (op == "add_note") {
        const auto key = a.value("key"), pos = a.value("position"), length = a.value("length");
        if (!key.isDouble() || key.toInt() < 0 || key.toInt() > 127
            || !pos.isDouble() || pos.toInt() < 0 || pos.toInt() > 10000000
            || !length.isDouble() || length.toInt() < 1 || length.toInt() > 1000000) {
            err("Invalid MIDI note; key 0..127, position >= 0, length > 0");
        }
    } else err("Unsupported edit operation");
}
QJsonObject propose(const QJsonObject& a) {
    validEdit(a);
    const QString path = checkedPath(a);
    const QByteArray bytes = readBounded(path);
    const auto doc = parseProject(bytes);
    if (a.value("operation").toString() == "add_note" && doc.elementsByTagName("pattern").count() == 0) {
        err("No pattern in project; create a pattern in the DAW first");
    }
    if (pending.size() >= 64) pending.clear();
    const QString plan = QUuid::createUuid().toString(QUuid::WithoutBraces);
    pending.insert(plan, Pending{
        path, QCryptographicHash::hash(bytes, QCryptographicHash::Sha256),
        a.value("operation").toString(), a
    });
    return QJsonObject{
        {"plan_id", plan},
        {"operation", a.value("operation").toString()},
        {"target", QFileInfo(path).fileName()},
        {"preview_only", true},
        {"writes_enabled", writesEnabled},
        {"message", "No project was modified. Review the change in your MCP host before applying."}
    };
}
QJsonObject apply(const QJsonObject& a) {
    if (!writesEnabled) err("Writes disabled. Launch with NOEMIXERR_ALLOW_WRITES=1 to enable.");
    if (!a.value("confirm").toBool()) err("Explicit confirm=true is required");
    const QString plan = a.value("plan_id").toString();
    if (!pending.contains(plan)) err("Unknown or expired plan identifier");
    const Pending p = pending.take(plan);
    // Revalidate scope and content at the moment of writing.
    const QString path = checkedPath(QJsonObject{{"path", p.canonicalPath}});
    if (path != p.canonicalPath) err("Project path changed");
    const QByteArray oldData = readBounded(path);
    if (QCryptographicHash::hash(oldData, QCryptographicHash::Sha256) != p.fingerprint) {
        err("The project changed since preview; propose again");
    }
    QDomDocument doc = parseProject(oldData);
    if (p.operation == "set_tempo") {
        auto head = doc.documentElement().firstChildElement("head");
        if (head.isNull()) err("Missing song head");
        head.setAttribute("bpm", p.args.value("bpm").toDouble());
    } else if (p.operation == "add_note") {
        QDomElement pattern = doc.documentElement().elementsByTagName("pattern").item(0).toElement();
        if (pattern.isNull()) err("Pattern missing");
        QDomElement note = doc.createElement("note");
        note.setAttribute("key", p.args.value("key").toInt());
        note.setAttribute("pos", p.args.value("position").toInt());
        note.setAttribute("len", p.args.value("length").toInt());
        note.setAttribute("vol", 100);
        pattern.appendChild(note);
    } else err("Invalid pending operation");
    const QString backup = path + ".noemixerr-" +
        QDateTime::currentDateTimeUtc().toString("yyyyMMddTHHmmsszzz") +
        "-" + QUuid::createUuid().toString(QUuid::WithoutBraces) + ".bak";
    if (!QFile::copy(path, backup)) err("Cannot create recovery backup");
    QSaveFile output(path);
    if (!output.open(QIODevice::WriteOnly)) err("Cannot open atomic project save");
    const QByteArray written = doc.toByteArray(2);
    if (output.write(written) != written.size() || !output.commit()) {
        err("Atomic save failed; recovery backup retained");
    }
    return QJsonObject{
        {"applied", true},
        {"operation", p.operation},
        {"backup", QFileInfo(backup).fileName()},
        {"message", "Saved atomically; original project retained as recovery backup"}
    };
}
QJsonObject toolList() {
    return objectLiteral(R"json({
      "tools":[
        {"name":"inspect_project","description":"Read BPM, tracks and notes from a local LMMS/NoeMixerr .mmp project without changing it",
          "inputSchema":{"type":"object","properties":{"path":{"type":"string"}},"required":["path"]},
          "annotations":{"readOnlyHint":true}},
        {"name":"propose_edit","description":"Preview a reversible tempo or piano-roll note edit; no files changed",
          "inputSchema":{"type":"object","properties":{
            "path":{"type":"string"},"operation":{"type":"string","enum":["set_tempo","add_note"]},
            "bpm":{"type":"number"},"key":{"type":"integer"},"position":{"type":"integer"},"length":{"type":"integer"}},
            "required":["path","operation"]},
          "annotations":{"readOnlyHint":true}},
        {"name":"apply_edit","description":"Write a previously proposed edit with a recovery backup; disabled unless enabled by user. Approval must be enforced by MCP host.",
          "inputSchema":{"type":"object","properties":{
            "plan_id":{"type":"string"},"confirm":{"type":"boolean"}},
            "required":["plan_id","confirm"]},
          "annotations":{"readOnlyHint":false,"destructiveHint":true}}
      ]
    })json");
}
QJsonObject dispatch(const QJsonObject& request) {
    const QString method = request.value("method").toString();
    if (method == "initialize") {
        return QJsonObject{
            {"protocolVersion","2025-03-26"},
            {"capabilities",QJsonObject{{"tools",QJsonObject{}}}},
            {"serverInfo",QJsonObject{{"name","noemixerr-mcp"},{"version","0.1.0-dev"}}}
        };
    }
    if (method == "ping") return QJsonObject{};
    if (method == "tools/list") return toolList();
    if (method == "tools/call") {
        const QJsonObject params = request.value("params").toObject();
        const QString name = params.value("name").toString();
        const QJsonObject args = params.value("arguments").toObject();
        try {
            if (name == "inspect_project") return textResult(inspect(args));
            if (name == "propose_edit") return textResult(propose(args));
            if (name == "apply_edit") return textResult(apply(args));
            return toolError("Unknown MCP tool");
        } catch (const std::exception& e) { return toolError(QString::fromUtf8(e.what())); }
    }
    err("Method not found");
    return QJsonObject{};
}
}
int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    if (app.arguments().contains("--version")) {
        std::puts("NoeMixerr MCP 0.1.0-dev");
        return 0;
    }
    QFileInfo dir(qEnvironmentVariable("NOEMIXERR_WORKSPACE", QDir::currentPath()));
    workspace = dir.canonicalFilePath();
    if (workspace.isEmpty() || !QFileInfo(workspace).isDir()) {
        std::fputs("NOEMIXERR_WORKSPACE must be an existing directory\n", stderr);
        return 2;
    }
    writesEnabled = qEnvironmentVariable("NOEMIXERR_ALLOW_WRITES") == "1";
    QTextStream input(stdin, QIODevice::ReadOnly);
    QTextStream output(stdout, QIODevice::WriteOnly);
    while (!input.atEnd()) {
        const QString line = input.readLine();
        if (line.isEmpty()) continue;
        QJsonObject response{{"jsonrpc","2.0"}};
        try {
            const auto request = object(line.toUtf8());
            if (!request.contains("id")) continue;
            response.insert("id", request.value("id"));
            try {
                response.insert("result", dispatch(request));
            } catch (const std::exception& e) {
                response.insert("error", QJsonObject{{"code",-32601},{"message",QString::fromUtf8(e.what())}});
            }
        } catch (const std::exception& e) {
            response.insert("id", QJsonValue::Null);
            response.insert("error", QJsonObject{{"code",-32700},{"message",QString::fromUtf8(e.what())}});
        }
        output << QString::fromUtf8(QJsonDocument(response).toJson(QJsonDocument::Compact)) << '\n';
        output.flush();
    }
    return 0;
}
