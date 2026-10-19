// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2013 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 

#include <QMouseEvent>
#include <QPainter>

#include "PixmapButton.h"
#include "embed.h"

namespace noemixerr::gui
{


PixmapButton::PixmapButton( QWidget * _parent, const QString & _name ) :
	AutomatableButton( _parent, _name ),
	m_activePixmap(),
	m_inactivePixmap(),
	m_pressed( false )
{
	setActiveGraphic( embed::getIconPixmap( "led_yellow" ) );
	setInactiveGraphic( embed::getIconPixmap( "led_off" ), false );
}







void PixmapButton::paintEvent(QPaintEvent*)
{
	QPainter p(this);

	QPixmap* pixmapToDraw = isActive() ? &m_activePixmap : &m_inactivePixmap;

	if (!pixmapToDraw->isNull())
	{
		p.drawPixmap(0, 0, *pixmapToDraw);
	}
}





void PixmapButton::mousePressEvent( QMouseEvent * _me )
{
	// Show pressing graphics if this isn't checkable
	if( !isCheckable() )
	{
		m_pressed = true;
		update();
	}

	AutomatableButton::mousePressEvent( _me );
}




void PixmapButton::mouseReleaseEvent( QMouseEvent * _me )
{
	AutomatableButton::mouseReleaseEvent( _me );

	if( !isCheckable() )
	{
		m_pressed = false;
		update();
	}
}




void PixmapButton::mouseDoubleClickEvent( QMouseEvent * _me )
{
	emit doubleClicked();
	_me->accept();
}


void PixmapButton::setActiveGraphic(const QPixmap &pm)
{
	m_activePixmap = pm;
	resize(embed::logicalSize(m_activePixmap));
}


void PixmapButton::setInactiveGraphic( const QPixmap & _pm, bool _update )
{
	m_inactivePixmap = _pm;
	if( _update )
	{
		update();
	}
}

QSize PixmapButton::sizeHint() const
{
	return minimumSizeHint();
}

QSize PixmapButton::minimumSizeHint() const
{
	return embed::logicalSize(m_activePixmap)
		.expandedTo(embed::logicalSize(m_inactivePixmap));
}

bool PixmapButton::isActive() const
{
	return (model() != nullptr && model()->value()) || m_pressed;
}

} // namespace noemixerr::gui
