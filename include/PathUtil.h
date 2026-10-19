// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019-2022 Spekular <Spekularr@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PATHUTIL_H
#define NoeMixerr_PATHUTIL_H

#include <filesystem>
#include <string_view>

#include <QDir>

#include "noemixerr_export.h"

namespace noemixerr::PathUtil
{
	enum class Base { Absolute, ProjectDir, FactoryProjects, FactorySample, UserSample, UserVST, Preset,
		FactoryPresets, UserLADSPA, DefaultLADSPA, UserSoundfont, DefaultSoundfont, UserGIG, DefaultGIG,
		LocalDir };

	//! Return the directory associated with a given base as a QString
	//! Optionally, if a pointer to boolean is given the method will
	//! use it to indicate whether the prefix could be resolved properly
	//! or not.
	QString NOEMIXERR_EXPORT baseLocation(const Base base, bool* error = nullptr);
	//! Return the directory associated with a given base as a QDir.
	//! Optional pointer to boolean to indicate if the prefix could
	//! be resolved properly.
	QDir NOEMIXERR_EXPORT baseQDir (const Base base, bool* error = nullptr);
	//! Return the prefix used to denote this base in path strings
	QString NOEMIXERR_EXPORT basePrefix(const Base base);
	//! Check the prefix of a path and return the base it corresponds to
	//! Defaults to Base::Absolute
	Base NOEMIXERR_EXPORT baseLookup(const QString& input);

	//! Remove the prefix from a path, iff there is one
	QString NOEMIXERR_EXPORT stripPrefix(const QString& input);
	//! Get the filename for a path, handling prefixed paths correctly
	QString NOEMIXERR_EXPORT cleanName(const QString& input);

	//! Upgrade prefix-less relative paths to the new format
	QString NOEMIXERR_EXPORT oldRelativeUpgrade(const QString& input);

	//! Make this path absolute. If a pointer to boolean is given
	//! it will indicate whether the path was converted successfully
	QString NOEMIXERR_EXPORT toAbsolute(const QString& input, bool* error = nullptr);
	//! Make this path relative to a given base, return an absolute path if that fails
	QString NOEMIXERR_EXPORT relativeOrAbsolute(const QString& input, const Base base);
	//! Make this path relative to any base, choosing the shortest if there are
	//! multiple options. allowLocal defines whether local paths should be considered.
	//! Defaults to an absolute path if all bases fail.
	QString NOEMIXERR_EXPORT toShortestRelative(const QString& input, bool allowLocal = false);

	//! Converts a UTF-8 encoded string to std::filesystem::path
	NOEMIXERR_EXPORT auto stringToPath(std::string_view path) -> std::filesystem::path;

	//! Converts QString to std::filesystem::path
	NOEMIXERR_EXPORT auto stringToPath(const QString& path) -> std::filesystem::path;

	//! Converts std::filesystem::path to a UTF-8 encoded std::string
	NOEMIXERR_EXPORT auto pathToString(const std::filesystem::path& path) -> std::string;
} // namespace noemixerr::PathUtil

#endif // NoeMixerr_PATHUTIL_H
