// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_CONTROLLER_H
#define NoeMixerr_MIDI_CONTROLLER_H

#include <QWidget>

#include "AutomatableModel.h"
#include "Controller.h"
#include "MidiEventProcessor.h"
#include "MidiPort.h"


namespace noemixerr
{

class MidiPort;

namespace gui
{
class ControllerConnectionDialog;
}


class MidiController : public Controller, public MidiEventProcessor
{
	Q_OBJECT
public:
	static constexpr int NONE = -1;
	MidiController( Model * _parent );
	~MidiController() override = default;

	void processInEvent( const MidiEvent & _me,
					const TimePos & _time, f_cnt_t offset = 0 ) override;

	void processOutEvent( const MidiEvent& _me,
					const TimePos & _time, f_cnt_t offset = 0 ) override
	{
		// No output yet
	}

	void saveSettings( QDomDocument & _doc, QDomElement & _this ) override;
	void loadSettings( const QDomElement & _this ) override;
	QString nodeName() const override;

	// Used by controllerConnectionDialog to copy
	void subscribeReadablePorts( const MidiPort::Map & _map );


public slots:
	gui::ControllerDialog* createDialog( QWidget * _parent ) override;
	void updateName();


protected:
	// The internal per-controller get-value function
	void updateValueBuffer() override;


	MidiPort m_midiPort;


	float m_lastValue;
	float m_previousValue;

	friend class gui::ControllerConnectionDialog;
	friend class AutoDetectMidiController;

} ;


} // namespace noemixerr

#endif // NoeMixerr_MIDI_CONTROLLER_H
