// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_INSTRUMENT_FUNCTION_VIEWS_H
#define NoeMixerr_INSTRUMENT_FUNCTION_VIEWS_H

#include "ModelView.h"

#include <QWidget>

class QLabel;

namespace noemixerr
{

class InstrumentFunctionArpeggio;
class InstrumentFunctionNoteStacking;

namespace gui
{

class ComboBox;
class GroupBox;
class Knob;
class TempoSyncKnob;

class InstrumentFunctionNoteStackingView : public QWidget, public ModelView
{
	Q_OBJECT
public:
	InstrumentFunctionNoteStackingView( InstrumentFunctionNoteStacking* cc, QWidget* parent = nullptr );
	~InstrumentFunctionNoteStackingView() override;


private:
	void modelChanged() override;

	InstrumentFunctionNoteStacking * m_cc;

	GroupBox * m_chordsGroupBox;
	ComboBox * m_chordsComboBox;
	Knob * m_chordRangeKnob;

} ;





class InstrumentFunctionArpeggioView : public QWidget, public ModelView
{
	Q_OBJECT
public:
	InstrumentFunctionArpeggioView( InstrumentFunctionArpeggio* arp, QWidget* parent = nullptr );
	~InstrumentFunctionArpeggioView() override;


private:
	void modelChanged() override;

	InstrumentFunctionArpeggio * m_a;
	GroupBox * m_arpGroupBox;
	ComboBox * m_arpComboBox;
	Knob * m_arpRangeKnob;
	Knob * m_arpRepeatsKnob;
	Knob * m_arpCycleKnob;
	Knob * m_arpSkipKnob;
	Knob * m_arpMissKnob;
	TempoSyncKnob * m_arpTimeKnob;
	Knob * m_arpGateKnob;

	ComboBox * m_arpDirectionComboBox;
	ComboBox * m_arpModeComboBox;

} ;

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_INSTRUMENT_FUNCTION_VIEWS_H
