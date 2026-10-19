// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2006 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 

#include <QMouseEvent>

#include "NStateButton.h"


namespace noemixerr::gui
{


NStateButton::NStateButton( QWidget * _parent ) :
	ToolButton( _parent ),
	m_generalToolTip( "" ),
	m_curState( -1 )
{
}




NStateButton::~NStateButton()
{
	while( m_states.size() )
	{
		m_states.erase( m_states.begin() );
	}
}




void NStateButton::addState( const QPixmap & _pm, const QString & _tooltip )
{
	m_states.push_back( qMakePair( _pm, _tooltip ) );
	// first inserted pixmap?
	if( m_states.size() == 1 )
	{
		// and set state to first pixmap
		changeState( 0 );
	}
}




void NStateButton::changeState(int state)
{
	if (state >= 0 && state < m_states.size() && state != m_curState)
	{
		m_curState = state;

		const auto& [icon, tooltip] = m_states[m_curState];
		setToolTip(tooltip.isEmpty() ? m_generalToolTip : tooltip);
		setIcon(icon);

		emit changedState(m_curState);
	}
}

void NStateButton::mousePressEvent(QMouseEvent* me)
{
	if (me->button() == Qt::LeftButton && !m_states.empty())
	{
		changeState((m_curState + 1) % m_states.size());
	}
	ToolButton::mousePressEvent(me);
}

} // namespace noemixerr::gui
