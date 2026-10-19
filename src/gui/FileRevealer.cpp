// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Andrew Wiltshire <aw1lt / at/ proton/ dot/me >
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "FileRevealer.h"

#include <QDesktopServices>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QString>
#include <QRegularExpression>
#include <QUrl>
#include <optional>

#include "noemixerrconfig.h"

namespace noemixerr::gui {
bool FileRevealer::s_canSelect = false;

const QString& FileRevealer::getDefaultFileManager()
{
	static std::optional<QString> fileManagerCache;
	if (fileManagerCache.has_value()) { return fileManagerCache.value(); }
#if defined(NoeMixerr_BUILD_WIN32)
	fileManagerCache = "explorer";
#elif defined(NoeMixerr_BUILD_APPLE)
	fileManagerCache = "open";
#else

	QString desktopEnv = qgetenv("XDG_CURRENT_DESKTOP").trimmed().toLower();

	if (desktopEnv.contains("xfce"))
	{
		fileManagerCache = "exo-open";
		return fileManagerCache.value();
	}

	QProcess process;
	if (desktopEnv.contains("gnome"))
	{
		process.start("gio", {"mime", "inode/directory"});
	}
	else
	{
		process.start("xdg-mime", {"query", "default", "inode/directory"});
	}

	process.waitForFinished(3000);

	QString fileManager = QString::fromUtf8(process.readAllStandardOutput()).toLower().trimmed();

	if (fileManager.contains("inode/directory"))
	{
		// gio format: split on ":" or "\n", take second element
		QStringList fileManagers = fileManager.split(QRegularExpression("[:\n]"), Qt::SkipEmptyParts);
		if (fileManagers.length() >= 2)
		{
			fileManagers.removeFirst();
			fileManager = fileManagers.first().trimmed();
		}
		else
		{
			// Fallback to something sane
			fileManager = "xdg-open";
		}
	}
	else
	{
		// xdg-mime format: split on ";", take the last non-empty element
		QStringList fileManagers = fileManager.split(';', Qt::SkipEmptyParts);
		if (!fileManagers.isEmpty())
		{
			// The highest priority file manager is last
			fileManager = fileManagers.last();
		}
	}

	if (fileManager.endsWith(".desktop")) { fileManager.chop(8); }

	// If the fileManager contains dots (e.g., "org.kde.dolphin"), extract only the last part
	fileManager = fileManager.section('.', -1);
	fileManagerCache = fileManager;
#endif
	qDebug() << "FileRevealer: Default app for inode/directory:" << fileManagerCache.value();
	return fileManagerCache.value();
}

void FileRevealer::openDir(const QFileInfo item)
{
	QString nativePath = QDir::toNativeSeparators(item.canonicalFilePath());

	QProcess::startDetached(getDefaultFileManager(), {nativePath});
}

const QStringList& FileRevealer::getSelectCommand()
{
	static std::optional<QStringList> selectCommandCache;

	if (selectCommandCache.has_value()) { return selectCommandCache.value(); }

	static const std::map<QString, QStringList> argMap = {
		{"open", {"-R"}},
		{"explorer", {"/select,"}},
		{"nemo", {}},
		{"thunar", {}},
		{"exo-open", {"--launch", "FileManager"}},
	};

	// Skip calling "--help" for file managers that we know
	for (const auto& [fileManager, arg] : argMap)
	{
		if (fileManager == getDefaultFileManager())
		{
			s_canSelect = true;
			selectCommandCache = arg;
			return selectCommandCache.value();
		}
	}

	// Parse "<command> --help" and look for the "--select" for file managers that we don't know
	if (supportsArg(getDefaultFileManager(), "--select"))
	{
		s_canSelect = true;
		selectCommandCache = {"--select"};
		return selectCommandCache.value();
	}

	// Fallback to empty list
	selectCommandCache = QStringList{};
	return selectCommandCache.value();
}

void FileRevealer::reveal(const QFileInfo item)
{
	// Sets selectCommandCache, canSelect
	const QStringList& selectCommand = getSelectCommand();
	if (!s_canSelect)
	{
		QDesktopServices::openUrl(QUrl::fromLocalFile(item.canonicalPath()));
		return;
	}

	QString path = QDir::toNativeSeparators(item.canonicalFilePath());
	QStringList params;

	if (!selectCommand.isEmpty()) { params << selectCommand; }

	params << path;
	QProcess::startDetached(getDefaultFileManager(), params);
}

bool FileRevealer::supportsArg(const QString& command, const QString& arg)
{
	QProcess process;
	process.start(command, {"--help"});
	process.waitForFinished(3000);

	QString output = process.readAllStandardOutput() + process.readAllStandardError();
	return output.contains(arg);
}

} // namespace noemixerr::gui
