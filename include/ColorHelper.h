// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024- Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_COLOR_HELPER_H
#define NoeMixerr_GUI_COLOR_HELPER_H

#include <cmath>
#include <QColor>

namespace noemixerr::gui
{

class ColorHelper
{
public:
	static QColor interpolateInRgb(const QColor& a, const QColor& b, float t)
	{
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
		using ColorType = float;
#else
		using ColorType = qreal;
#endif

		ColorType ar, ag, ab, aa;
		a.getRgbF(&ar, &ag, &ab, &aa);

		ColorType br, bg, bb, ba;
		b.getRgbF(&br, &bg, &bb, &ba);

		const auto t2 = static_cast<ColorType>(t);
		const auto interH = std::lerp(ar, br, t2);
		const auto interS = std::lerp(ag, bg, t2);
		const auto interV = std::lerp(ab, bb, t2);
		const auto interA = std::lerp(aa, ba, t2);

		return QColor::fromRgbF(interH, interS, interV, interA);
	}
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_COLOR_HELPER_H
