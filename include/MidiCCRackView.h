// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020 Ian Caio <iancaio_dev/at/hotmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_MIDI_CC_RACK_VIEW_H
#define NoeMixerr_GUI_MIDI_CC_RACK_VIEW_H

#include <QWidget>

#include "Midi.h"
#include "SerializingObject.h"

namespace noemixerr
{

class InstrumentTrack;

namespace gui
{

class Knob;
class GroupBox;

class MidiCCRackView : public QWidget, public SerializingObject
{
	Q_OBJECT
public:
	MidiCCRackView(InstrumentTrack * track);
	~MidiCCRackView() override;

	void saveSettings(QDomDocument & doc, QDomElement & parent) override;
	void loadSettings(const QDomElement &) override;

	inline QString nodeName() const override
	{
		return "MidiCCRackView";
	}

private slots:
	void renameWindow();

private:
	InstrumentTrack *m_track;

	GroupBox *m_midiCCGroupBox; // MIDI CC GroupBox (used to enable disable MIDI CC)

	Knob *m_controllerKnob[MidiControllerCount]; // Holds the knob widgets for each controller

};


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_MIDI_CC_RACK_VIEW_H
