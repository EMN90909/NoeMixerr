// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_FONT_HELPER_H
#define NoeMixerr_GUI_FONT_HELPER_H

#include <QApplication>
#include <QFont>

constexpr int DEFAULT_FONT_SIZE = 12;
constexpr int SMALL_FONT_SIZE = 10;
constexpr int LARGE_FONT_SIZE = 14;

namespace noemixerr::gui
{

// Convenience method to set the font size in pixels
inline QFont adjustedToPixelSize(QFont font, int size)
{
	font.setPixelSize(size);
	return font;
}

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_FONT_HELPER_H
