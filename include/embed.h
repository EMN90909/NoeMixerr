// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_EMBED_H
#define NoeMixerr_EMBED_H

#include <string>
#include <string_view>

#include <QPixmap>
#include <QString>

#include "noemixerr_export.h"
#ifdef PLUGIN_NAME
#include "NoeMixerrCommonMacros.h"
#endif

namespace noemixerr {

namespace embed {

//! @brief Return an image for the icon pixmap cache.
//! @param name Identifier for the pixmap. If it is not in the icon pixmap cache, it will be loaded from the artwork
//! QDir search paths (exceptions are compiled-in XPMs, you need to provide @p xpm for loading them).
//! @param width A specific pixmap width. When this and @p height are provided, the pixmap is cached.
//! @param height A specific pixmap height. When this and @p width are provided, the pixmap is cached.
//! @param xpm Must be XPM data if the source should be raw XPM data instead of a file
auto NOEMIXERR_EXPORT getIconPixmap(
	std::string_view name,
	int width = -1,
	int height = -1,
	const char* const* xpm = nullptr
) -> QPixmap;

auto NOEMIXERR_EXPORT getText(std::string_view name) -> QString;

//! @brief Temporary shim for QPixmap::deviceIndependentSize.
//! @param pixmap The pixmap to get the size of.
//! @return The device-independent size of the pixmap.
inline auto logicalSize(const QPixmap& pixmap) noexcept
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 2, 0)
	return pixmap.deviceIndependentSize().toSize();
#else
	return pixmap.isNull() ? QSize(0, 0) : pixmap.size() / pixmap.devicePixelRatio();
#endif
}

} // namespace embed

class PixmapLoader
{
public:
	PixmapLoader() = default;

	explicit PixmapLoader(std::string name, const char* const* xpm = nullptr) :
		m_name{std::move(name)},
		m_xpm{xpm}
	{ }

	virtual ~PixmapLoader() = default;

	auto pixmap(int width = -1, int height = -1) const -> QPixmap
	{
		return embed::getIconPixmap(m_name, width, height, m_xpm);
	}

	auto pixmapName() const -> const std::string& { return m_name; }

private:
	std::string m_name;
	const char* const* m_xpm = nullptr;
};

#ifdef PLUGIN_NAME

class PluginPixmapLoader : public PixmapLoader
{
public:
	PluginPixmapLoader() = default;

	explicit PluginPixmapLoader(std::string name, const char* const* xpm = nullptr) :
		PixmapLoader{NoeMixerr_STRINGIFY(PLUGIN_NAME) "/" + name, xpm}
	{ }
};

namespace PLUGIN_NAME {

inline auto getIconPixmap(std::string_view name,
	int width = -1, int height = -1, const char* const* xpm = nullptr) -> QPixmap
{
	return PluginPixmapLoader{std::string{name}, xpm}.pixmap(width, height);
}

} // namespace PLUGIN_NAME

#endif // PLUGIN_NAME

} // namespace noemixerr

#endif // NoeMixerr_EMBED_H
