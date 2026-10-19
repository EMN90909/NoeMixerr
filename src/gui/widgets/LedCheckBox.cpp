// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "LedCheckBox.h"

#include <QFontMetrics>
#include <QPainter>
#include <array>

#include "DeprecationHelper.h"
#include "embed.h"
#include "FontHelper.h"

namespace noemixerr::gui
{


static const auto names = std::array<QString, 3>
{
	"led_yellow", "led_green", "led_red"
} ;




LedCheckBox::LedCheckBox( const QString & _text, QWidget * _parent,
				const QString & _name, LedColor _color, bool legacyMode ) :
	AutomatableButton( _parent, _name ),
	m_text( _text ),
	m_legacyMode(legacyMode)
{
	setLedColor(_color);
}




LedCheckBox::LedCheckBox( QWidget * _parent,
				const QString & _name, LedColor _color, bool legacyMode ) :
	LedCheckBox( QString(), _parent, _name, _color, legacyMode )
{
}

void LedCheckBox::setText( const QString &s )
{
	m_text = s;
	onTextUpdated();
}




void LedCheckBox::paintEvent( QPaintEvent * pe )
{
	if (!m_legacyMode)
	{
		paintNonLegacy(pe);
	}
	else
	{
		paintLegacy(pe);
	}
}




void LedCheckBox::setLedColor(LedColor color)
{
	setCheckable( true );

	m_ledOnPixmap = embed::getIconPixmap(names[static_cast<std::size_t>(color)].toUtf8().constData());
	m_ledOffPixmap = embed::getIconPixmap("led_off");

	if (m_legacyMode){ setFont(adjustedToPixelSize(font(), DEFAULT_FONT_SIZE)); }

	setText( m_text );
}




void LedCheckBox::onTextUpdated()
{
	QFontMetrics const fm = fontMetrics();

	int const width = m_ledOffPixmap.width() + 5 + fm.horizontalAdvance(text());
	int const height = m_legacyMode ? m_ledOffPixmap.height() : qMax(m_ledOffPixmap.height(), fm.height());

	setFixedSize(width, height);
}

void LedCheckBox::paintLegacy(QPaintEvent * pe)
{
	QPainter p( this );
	p.setFont(adjustedToPixelSize(font(), DEFAULT_FONT_SIZE));

	p.drawPixmap(0, 0, model()->value() ? m_ledOnPixmap : m_ledOffPixmap);

	p.setPen( QColor( 64, 64, 64 ) );
	p.drawText(m_ledOffPixmap.width() + 4, 11, text());
	p.setPen( QColor( 255, 255, 255 ) );
	p.drawText(m_ledOffPixmap.width() + 3, 10, text());
}

void LedCheckBox::paintNonLegacy(QPaintEvent * pe)
{
	QPainter p(this);

	auto drawnPixmap = model()->value() ? m_ledOnPixmap : m_ledOffPixmap;

	p.drawPixmap(0, rect().height() / 2 - drawnPixmap.height() / 2, drawnPixmap);

	QRect r = rect();
	r -= QMargins(m_ledOffPixmap.width() + 5, 0, 0, 0);
	p.drawText(r, text());
}


} // namespace noemixerr::gui
