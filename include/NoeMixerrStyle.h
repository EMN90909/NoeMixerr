// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_NoeMixerr_STYLE_H
#define NoeMixerr_GUI_NoeMixerr_STYLE_H

#include <QFileSystemWatcher>
#include <QProxyStyle>


namespace noemixerr::gui
{


class NoeMixerrStyle : public QProxyStyle
{
public:
	NoeMixerrStyle();
	~NoeMixerrStyle() override = default;

	QPalette standardPalette() const override;

	void drawComplexControl(
				ComplexControl control,
				const QStyleOptionComplex * option,
					QPainter *painter,
						const QWidget *widget ) const override;
	void drawPrimitive( PrimitiveElement element,
					const QStyleOption *option,
					QPainter *painter,
					const QWidget *widget = 0 ) const override;

	int pixelMetric( PixelMetric metric,
					const QStyleOption * option = 0,
					const QWidget * widget = 0 ) const override;

	static QPalette * s_palette;

private:
	QImage colorizeXpm( const char * const * xpm, const QBrush& fill ) const;
	void hoverColors( bool sunken, bool hover, bool active, QColor& color, QColor& blend ) const;
	QFileSystemWatcher m_styleReloader;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_NoeMixerr_STYLE_H
