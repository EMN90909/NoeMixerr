// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "MidiPortMenu.h"

namespace noemixerr::gui
{


MidiPortMenu::MidiPortMenu( MidiPort::Mode _mode ) :
	ModelView( nullptr, this ),
	m_mode( _mode )
{
	connect( this, SIGNAL(triggered(QAction*)),
			this, SLOT(activatedPort(QAction*)));
}





void MidiPortMenu::modelChanged()
{
	auto mp = castModel<MidiPort>();
	if( m_mode == MidiPort::Mode::Input )
	{
		connect( mp, SIGNAL(readablePortsChanged()),
				this, SLOT(updateMenu()));
	}
	else if( m_mode == MidiPort::Mode::Output )
	{
		connect( mp, SIGNAL(writablePortsChanged()),
				this, SLOT(updateMenu()));
	}
	updateMenu();
}




void MidiPortMenu::activatedPort( QAction * _item )
{
	if( m_mode == MidiPort::Mode::Input )
	{
		castModel<MidiPort>()->subscribeReadablePort( _item->text(),
							_item->isChecked() );
	}
	else if( m_mode == MidiPort::Mode::Output )
	{
		castModel<MidiPort>()->subscribeWritablePort( _item->text(),
							_item->isChecked() );
	}
}




void MidiPortMenu::updateMenu()
{
	auto mp = castModel<MidiPort>();
	const MidiPort::Map & map = ( m_mode == MidiPort::Mode::Input ) ?
				mp->readablePorts() : mp->writablePorts();
	clear();
	for( MidiPort::Map::ConstIterator it = map.begin();
							it != map.end(); ++it )
	{
		QAction * a = addAction( it.key() );
		a->setCheckable( true );
		a->setChecked( it.value() );
	}
}


} // namespace noemixerr::gui


