// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_INSTRUMENT_MIDI_IO_VIEW_H
#define NoeMixerr_GUI_INSTRUMENT_MIDI_IO_VIEW_H

#include <QWidget>

#include "ModelView.h"

class QToolButton;

namespace noemixerr
{

class InstrumentTrack;

namespace gui
{

class GroupBox;
class LcdSpinBox;
class LedCheckBox;


class InstrumentMidiIOView : public QWidget, public ModelView
{
	Q_OBJECT
public:
	InstrumentMidiIOView( QWidget* parent );
	~InstrumentMidiIOView() override = default;


private:
	void modelChanged() override;

	GroupBox * m_midiInputGroupBox;
	LcdSpinBox * m_inputChannelSpinBox;
	LcdSpinBox * m_fixedInputVelocitySpinBox;
	QToolButton * m_rpBtn;

	GroupBox * m_midiOutputGroupBox;
	LcdSpinBox * m_outputChannelSpinBox;
	LcdSpinBox * m_fixedOutputVelocitySpinBox;
	LcdSpinBox * m_outputProgramSpinBox;
	LcdSpinBox * m_fixedOutputNoteSpinBox;
	QToolButton * m_wpBtn;

	LcdSpinBox* m_baseVelocitySpinBox;

} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_INSTRUMENT_MIDI_IO_VIEW_H
