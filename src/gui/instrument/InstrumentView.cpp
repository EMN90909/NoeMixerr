// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QIcon>

#include "InstrumentView.h"
#include "embed.h"
#include "InstrumentTrackWindow.h"

namespace noemixerr::gui
{

InstrumentView::InstrumentView( Instrument * _Instrument, QWidget * _parent ) :
	PluginView( _Instrument, _parent )
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setModel( _Instrument );
	setAttribute( Qt::WA_DeleteOnClose, true );
}




InstrumentView::~InstrumentView()
{
	if( instrumentTrackWindow() )
	{
		instrumentTrackWindow()->m_instrumentView = nullptr;
	}
}




void InstrumentView::setModel( Model * _model, bool )
{
	if( dynamic_cast<Instrument *>( _model ) != nullptr )
	{
		ModelView::setModel( _model );
		instrumentTrackWindow()->setWindowIcon( model()->logo()->pixmap() );
		connect( model(), SIGNAL(destroyed(QObject*)), this, SLOT(close()));
	}
}




InstrumentTrackWindow * InstrumentView::instrumentTrackWindow()
{
	return( dynamic_cast<InstrumentTrackWindow *>(
					parentWidget()->parentWidget() ) );
}





} // namespace noemixerr::gui
