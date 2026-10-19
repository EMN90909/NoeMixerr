// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "ToolPlugin.h"
#include "ToolPluginView.h"

#include <QIcon>

#include "embed.h"
#include "GuiApplication.h"
#include "MainWindow.h"

namespace noemixerr::gui
{


ToolPluginView::ToolPluginView( ToolPlugin * _toolPlugin ) :
	PluginView( _toolPlugin, nullptr )
{
	getGUI()->mainWindow()->addWindowedWidget( this );
	parentWidget()->setAttribute( Qt::WA_DeleteOnClose, false );

	setWindowTitle( _toolPlugin->displayName() );
	setWindowIcon( _toolPlugin->descriptor()->logo->pixmap() );
}


} // namespace noemixerr::gui
