// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2017 Alexandre Almeida <http://m374lx.users.sourceforge.net/>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "TrackRenameLineEdit.h"

#include <QKeyEvent>

namespace noemixerr::gui
{


TrackRenameLineEdit::TrackRenameLineEdit( QWidget * parent ) :
	QLineEdit( parent )
{
}




void TrackRenameLineEdit::show()
{
	m_oldName = text();
	QLineEdit::show();
}




void TrackRenameLineEdit::keyPressEvent( QKeyEvent * ke )
{
	if( ke->key() == Qt::Key_Escape ) 
	{
		setText( m_oldName );
		hide();
	}
	
	QLineEdit::keyPressEvent( ke );
}


} // namespace noemixerr::gui