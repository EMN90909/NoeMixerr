// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "CaptionMenu.h"


namespace noemixerr::gui
{


CaptionMenu::CaptionMenu( const QString & _title, QWidget * _parent ) :
	QMenu( _title, _parent )
{
	QAction * caption = addAction( _title );
	caption->setEnabled( false );
}





} // namespace noemixerr::gui
