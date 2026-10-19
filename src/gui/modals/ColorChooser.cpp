// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020 russiankumar <adityakumar4644/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <ColorChooser.h>


namespace noemixerr::gui
{


void ColorChooser::setPalette (QVector<QColor> colors)
{
	const int max = qMin (colors.size(), 48);
	for (int i = 0; i < max; i++)
	{
		ColorChooser::setStandardColor (i, colors[i]);
	}
}


void ColorChooser::setPalette (Palette palette)
{
	setPalette (getPalette (palette));
}


ColorChooser* ColorChooser::withPalette (Palette palette)
{
	setPalette (palette);
	return this;
}


QVector<QColor> ColorChooser::getPalette (Palette palette)
{
	switch (palette)
	{
		case Palette::Mixer: return nicePalette(140);
		case Palette::Track: return nicePalette(150);
		default: return defaultPalette();
	}
}


QVector<QColor> ColorChooser::defaultPalette()
{
	QVector <QColor> result (48);
	for (int i = 0; i < 48; i++)
	{
		result[i] = (QColorDialog::standardColor(i));
	}
	return result;
}


QVector<QColor> ColorChooser::nicePalette (int base)
{
	QVector <QColor> result (48);
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			result[6 * x + y].setHsl (qMax(0, 44 * x - 1), 150 - 20 * y, base - 10 * y);
		}
	}
	return result;
}


} // namespace noemixerr::gui
