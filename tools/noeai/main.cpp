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

QDomElement findTrack(QDomDocument& doc, int index) {
    QDomElement song = doc.documentElement().firstChildElement("song");
    if (song.isNull()) err("Project has no song");
    QDomElement container = song.firstChildElement("trackcontainer");
    if (container.isNull()) err("Song has no arrangement track container");
    QDomElement track = container.firstChildElement("track");
    for (int i = 0; i < index && !track.isNull(); ++i) {
        track = track.nextSiblingElement("track");
    }
    if (track.isNull()) err("Track index out of range");
    return track;
}
int nonnegativeIndex(const QJsonObject& a, const char* name, int maximum) {
    const QJsonValue v = a.value(QLatin1String(name));
    const double d = v.isUndefined() ? 0.0 : v.toDouble(-1.0);
    if ((!v.isUndefined() && !v.isDouble()) || d < 0 || d > maximum || d != double(int(d))) {
        err(QString("Invalid %1").arg(QLatin1String(name)));
    }
    return int(d);
}
void validEdit(const QJsonObject& a) {
    const QString op = a.value("operation").toString();
    if (op == "set_tempo") {
        const auto bpm = a.value("bpm");
        if (!bpm.isDouble() || bpm.toDouble() < 20 || bpm.toDouble() > 400) err("BPM must be 20..400");
    } else if (op == "add_note") {
        const auto key = a.value("key"), pos = a.value("position"), length = a.value("length");
        if (!key.isDouble() || key.toDouble() != double(key.toInt()) || key.toInt() < 0 || key.toInt() > 127
            || !pos.isDouble() || pos.toDouble() != double(pos.toInt()) || pos.toInt() < 0 || pos.toInt() > 10000000
            || !length.isDouble() || length.toDouble() != double(length.toInt()) || length.toInt() < 1 || length.toInt() > 1000000) {
            err("Invalid MIDI note; key 0..127, position >= 0, length > 0");
        }
        (void) nonnegativeIndex(a, "pattern_index", 4096);
    } else if (op == "add_notes") {
        const QJsonValue v = a.value("notes");
        if (!v.isArray() || v.toArray().isEmpty() || v.toArray().size() > 256) {
            err("Batch must contain between 1 and 256 MIDI notes");
        }
        for (const auto& candidate : v.toArray()) {
            if (!candidate.isObject()) err("Invalid MIDI note object");
            QJsonObject single = candidate.toObject();
            single.insert("operation", "add_note");
            validEdit(single);
        }
    } else if (op == "create_instrument_track" || op == "create_pattern") {
        (void) nonnegativeIndex(a, "track_index", 127);
        const QString name = a.value("name").toString();
        if (name.isEmpty() || name.size() > 80) err("Track/pattern name must be 1..80 characters");
        if (op == "create_pattern") (void) nonnegativeIndex(a, "position", 10000000);
    } else if (op == "set_track_mix") {
        (void) nonnegativeIndex(a, "track_index", 127);
        if (!a.value("volume").isDouble() || a.value("volume").toDouble() < 0 || a.value("volume").toDouble() > 200
            || !a.value("pan").isDouble() || a.value("pan").toDouble() < -100 || a.value("pan").toDouble() > 100
            || !a.value("mute").isBool()) err("Mix values must be volume 0..200, pan -100..100, mute true/false");
    } else err("Unsupported edit operation");
}
QJsonObject inspect(const QJsonObject& args) {
    const QString path = checkedPath(args);
    QDomDocument doc = parseProject(readBounded(path));
    const QDomElement root = doc.documentElement();
    const QDomElement head = root.firstChildElement("head");
    if (head.isNull()) err("Missing song head");
    QJsonArray tracks;
    QDomElement song = root.firstChildElement("song");
    QDomElement container = song.firstChildElement("trackcontainer");
    QDomElement track = container.firstChildElement("track");
    for (int index = 0; !track.isNull() && index < 128; ++index) {
        const QDomElement it = track.firstChildElement("instrumenttrack");
        tracks.append(QJsonObject{
            {"index", index},
            {"name", track.attribute("name")},
            {"type", track.attribute("type")},
            {"instrument", it.firstChildElement("instrument").attribute("name")},
            {"patterns", track.elementsByTagName("pattern").count()},
            {"notes", track.elementsByTagName("note").count()},
            {"muted", track.attribute("muted", "0") == "1"},
            {"volume", it.attribute("vol", "100").toDouble()},
            {"pan", it.attribute("pan", "0").toDouble()}
        });
        track = track.nextSiblingElement("track");
    }
    return QJsonObject{
        {"path", QFileInfo(path).fileName()},
        {"root", root.tagName()},
        {"bpm", head.attribute("bpm").toDouble()},
        {"track_elements", doc.elementsByTagName("track").count()},
        {"tracks", tracks},
        {"notes", doc.elementsByTagName("note").count()},
        {"editable_patterns", doc.elementsByTagName("pattern").count()}
    };
}
void editProject(QDomDocument& doc, const QString& op, const QJsonObject& a) {
    validEdit(a);
    if (op == "set_tempo") {
        QDomElement head = doc.documentElement().firstChildElement("head");
        if (head.isNull()) err("Missing song head");
        head.setAttribute("bpm", a.value("bpm").toDouble());
    } else if (op == "add_note") {
        const int i = nonnegativeIndex(a, "pattern_index", 4096);
        QDomElement pattern = doc.documentElement().elementsByTagName("pattern").item(i).toElement();
        if (pattern.isNull()) err("Pattern index out of range");
        QDomElement note = doc.createElement("note");
        note.setAttribute("key", a.value("key").toInt());
        note.setAttribute("pos", a.value("position").toInt());
        note.setAttribute("len", a.value("length").toInt());
        note.setAttribute("vol", 100);
        note.setAttribute("pan", 0);
        pattern.appendChild(note);
    } else if (op == "add_notes") {
        for (const auto& candidate : a.value("notes").toArray()) {
            QJsonObject single = candidate.toObject();
            single.insert("operation", "add_note");
            editProject(doc, "add_note", single);
        }
    } else if (op == "create_instrument_track") {
        QDomElement templateTrack = findTrack(doc, nonnegativeIndex(a, "track_index", 127));
        if (templateTrack.attribute("type") != "0" || templateTrack.firstChildElement("instrumenttrack").isNull()) {
            err("Template must be a top-level instrument track");
        }
        QDomElement parent = templateTrack.parentNode().toElement();
        if (parent.elementsByTagName("track").count() >= 128) err("Track limit reached");
        QDomElement track = templateTrack.cloneNode(true).toElement();
        track.setAttribute("name", a.value("name").toString());
        track.setAttribute("muted", 0);
        track.setAttribute("solo", 0);
        while (!track.firstChildElement("pattern").isNull()) {
            track.removeChild(track.firstChildElement("pattern"));
        }
        QDomElement pattern = doc.createElement("pattern");
        pattern.setAttribute("type", 1);
        pattern.setAttribute("muted", 0);
        pattern.setAttribute("steps", 16);
        pattern.setAttribute("pos", 0);
        pattern.setAttribute("len", 192);
        pattern.setAttribute("name", a.value("name").toString());
        track.appendChild(pattern);
        parent.appendChild(track);
    } else if (op == "create_pattern") {
        QDomElement track = findTrack(doc, nonnegativeIndex(a, "track_index", 127));
        if (track.attribute("type") != "0" || track.firstChildElement("instrumenttrack").isNull()) {
            err("Patterns can be created on instrument tracks only");
        }
        QDomElement pattern = doc.createElement("pattern");
        pattern.setAttribute("type", 1);
        pattern.setAttribute("muted", 0);
        pattern.setAttribute("steps", 16);
        pattern.setAttribute("pos", nonnegativeIndex(a, "position", 10000000));
        pattern.setAttribute("len", 192);
        pattern.setAttribute("name", a.value("name").toString());
        track.appendChild(pattern);
    } else if (op == "set_track_mix") {
        QDomElement track = findTrack(doc, nonnegativeIndex(a, "track_index", 127));
        QDomElement instrument = track.firstChildElement("instrumenttrack");
        if (instrument.isNull()) err("Only instrument tracks support this mix edit");
        instrument.setAttribute("vol", a.value("volume").toDouble());
        instrument.setAttribute("pan", a.value("pan").toDouble());
        track.setAttribute("muted", a.value("mute").toBool() ? 1 : 0);
    } else err("Unsupported edit operation");
}
QJsonObject propose(const QJsonObject& a) {
    validEdit(a);
    const QString path = checkedPath(a);
    const QByteArray bytes = readBounded(path);
    auto doc = parseProject(bytes);
    // Validate the exact target *before* creating a plan.
    editProject(doc, a.value("operation").toString(), a);
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
        {"parameters", a},
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
    const QString path = checkedPath(QJsonObject{{"path", p.canonicalPath}});
    if (path != p.canonicalPath) err("Project path changed");
    const QByteArray oldData = readBounded(path);
    if (QCryptographicHash::hash(oldData, QCryptographicHash::Sha256) != p.fingerprint) {
        err("The project changed since preview; propose again");
    }
    QDomDocument doc = parseProject(oldData);
    editProject(doc, p.operation, p.args);
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
        {"name":"inspect_project","description":"Inspect tempo and top-level tracks, instrument names, patterns and notes in a local LMMS/NoeMixerr .mmp project",
          "inputSchema":{"type":"object","properties":{"path":{"type":"string"}},"required":["path"]},
          "annotations":{"readOnlyHint":true}},
        {"name":"propose_edit","description":"Preview a tempo, note, instrument track, pattern or track-mix edit without writing any file",
          "inputSchema":{"type":"object","properties":{
            "path":{"type":"string"},"operation":{"type":"string","enum":["set_tempo","add_note","add_notes","create_instrument_track","create_pattern","set_track_mix"]},
            "bpm":{"type":"number"},"key":{"type":"integer"},"position":{"type":"integer"},
            "length":{"type":"integer"},"pattern_index":{"type":"integer"},
            "track_index":{"type":"integer"},"name":{"type":"string"},
            "volume":{"type":"number"},"pan":{"type":"number"},"mute":{"type":"boolean"},
            "notes":{"type":"array","minItems":1,"maxItems":256,"items":{"type":"object","properties":{
              "key":{"type":"integer","minimum":0,"maximum":127},
              "position":{"type":"integer","minimum":0},
              "length":{"type":"integer","minimum":1},
              "pattern_index":{"type":"integer","minimum":0}},
              "required":["key","position","length"]}}},
            "required":["path","operation"]},
          "annotations":{"readOnlyHint":true}},
        {"name":"apply_edit","description":"Save previously previewed edit atomically, with backup, after independent host approval. Disabled by default.",
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
