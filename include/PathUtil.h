/*
 * PathUtil.h
 *
 * Copyright (c) 2019-2022 Spekular <Spekularr@gmail.com>
 *
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

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
	QString NoeMixerr_EXPORT baseLocation(const Base base, bool* error = nullptr);
	//! Return the directory associated with a given base as a QDir.
	//! Optional pointer to boolean to indicate if the prefix could
	//! be resolved properly.
	QDir NoeMixerr_EXPORT baseQDir (const Base base, bool* error = nullptr);
	//! Return the prefix used to denote this base in path strings
	QString NoeMixerr_EXPORT basePrefix(const Base base);
	//! Check the prefix of a path and return the base it corresponds to
	//! Defaults to Base::Absolute
	Base NoeMixerr_EXPORT baseLookup(const QString& input);

	//! Remove the prefix from a path, iff there is one
	QString NoeMixerr_EXPORT stripPrefix(const QString& input);
	//! Get the filename for a path, handling prefixed paths correctly
	QString NoeMixerr_EXPORT cleanName(const QString& input);

	//! Upgrade prefix-less relative paths to the new format
	QString NoeMixerr_EXPORT oldRelativeUpgrade(const QString& input);

	//! Make this path absolute. If a pointer to boolean is given
	//! it will indicate whether the path was converted successfully
	QString NoeMixerr_EXPORT toAbsolute(const QString& input, bool* error = nullptr);
	//! Make this path relative to a given base, return an absolute path if that fails
	QString NoeMixerr_EXPORT relativeOrAbsolute(const QString& input, const Base base);
	//! Make this path relative to any base, choosing the shortest if there are
	//! multiple options. allowLocal defines whether local paths should be considered.
	//! Defaults to an absolute path if all bases fail.
	QString NoeMixerr_EXPORT toShortestRelative(const QString& input, bool allowLocal = false);

	//! Converts a UTF-8 encoded string to std::filesystem::path
	NoeMixerr_EXPORT auto stringToPath(std::string_view path) -> std::filesystem::path;

	//! Converts QString to std::filesystem::path
	NoeMixerr_EXPORT auto stringToPath(const QString& path) -> std::filesystem::path;

	//! Converts std::filesystem::path to a UTF-8 encoded std::string
	NoeMixerr_EXPORT auto pathToString(const std::filesystem::path& path) -> std::string;
} // namespace noemixerr::PathUtil

#endif // NoeMixerr_PATHUTIL_H
