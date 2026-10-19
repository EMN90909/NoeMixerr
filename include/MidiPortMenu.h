// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_MIDI_PORT_MENU_H
#define NoeMixerr_GUI_MIDI_PORT_MENU_H

#include <QMenu>

#include "ModelView.h"
#include "MidiPort.h"

class QAction;

namespace noemixerr::gui
{

class MidiPortMenu : public QMenu, public ModelView
{
	Q_OBJECT
public:
	MidiPortMenu( MidiPort::Mode _mode );
	~MidiPortMenu() override = default;


public slots:
	void updateMenu();


protected slots:
	void activatedPort( QAction * _item );


private:
	void modelChanged() override;

	MidiPort::Mode m_mode;

} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_MIDI_PORT_MENU_H
