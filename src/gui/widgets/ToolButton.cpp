// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2006 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 

#include "ToolButton.h"

namespace noemixerr::gui
{


ToolButton::ToolButton( const QPixmap & _pixmap, const QString & _tooltip,
			QObject * _receiver, const char * _slot,
			QWidget * _parent ) :
	QToolButton( _parent )
{
	setAutoFillBackground( false );

	if( _receiver != nullptr && _slot != nullptr )
	{
		connect( this, SIGNAL(clicked()), _receiver, _slot );
	}
	setToolTip(_tooltip);
	setIcon( _pixmap );
}


} // namespace noemixerr::gui