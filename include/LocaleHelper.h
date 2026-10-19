// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2018 Hyunjin Song <tteu.ingog/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


// NOTE: The NoeMixerr/zynaddsubfx repo contains a copy of this header.
//       If you modify this file, consider modifying it there as well.

#ifndef NoeMixerr_LOCALEHELPER_H
#define NoeMixerr_LOCALEHELPER_H

#include <QLocale>

#include <limits>
#include <cmath>

namespace noemixerr::LocaleHelper
{

inline double toDouble(const QString& str, bool* ok = nullptr)
{
	bool isOkay;
	QLocale c(QLocale::C);
	c.setNumberOptions(QLocale::RejectGroupSeparator);
	double value = c.toDouble(str, &isOkay);
	if (!isOkay)
	{
		QLocale german(QLocale::German);
		german.setNumberOptions(QLocale::RejectGroupSeparator);
		value = german.toDouble(str, &isOkay);
	}
	if (ok != nullptr) { *ok = isOkay; }
	return value;
}

inline float toFloat(const QString& str, bool* ok = nullptr)
{
	double d = toDouble(str, ok);
	if (!std::isinf(d) && std::fabs(d) > std::numeric_limits<float>::max())
	{
		if (ok != nullptr) { *ok = false; }
		return 0.0f;
	}
	return static_cast<float>(d);
}


} // namespace noemixerr::LocaleHelper

#endif // NoeMixerr_LOCALEHELPER_H
