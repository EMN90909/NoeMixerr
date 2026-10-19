// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2014 grejppi <grejppi/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_KICKER_H
#define NoeMixerr_KICKER_H

#include "AutomatableModel.h"
#include "Instrument.h"
#include "InstrumentView.h"
#include "TempoSyncKnobModel.h"


namespace noemixerr
{

#define KICKER_PRESET_VERSION 1


class NotePlayHandle;  // IWYU pragma: keep

namespace gui
{
class Knob;
class LedCheckBox;
class KickerInstrumentView;
}


class KickerInstrument : public Instrument
{
	Q_OBJECT
public:
	KickerInstrument( InstrumentTrack * _instrument_track );
	~KickerInstrument() override = default;

	void playNote( NotePlayHandle * _n,
						SampleFrame* _working_buffer ) override;
	void deleteNotePluginData( NotePlayHandle * _n ) override;

	void saveSettings(QDomDocument& doc, QDomElement& elem) override;
	void loadSettings(const QDomElement& elem) override;

	QString nodeName() const override;

	float desiredReleaseTimeMs() const override
	{
		return 12.f;
	}

	gui::PluginView* instantiateView( QWidget * _parent ) override;


private:
	FloatModel m_startFreqModel;
	FloatModel m_endFreqModel;
	TempoSyncKnobModel m_decayModel;
	FloatModel m_distModel;
	FloatModel m_distEndModel;
	FloatModel m_gainModel;
	FloatModel m_envModel;
	FloatModel m_noiseModel;
	FloatModel m_clickModel;
	FloatModel m_slopeModel;

	BoolModel m_startNoteModel;
	BoolModel m_endNoteModel;

	IntModel m_versionModel;

	friend class gui::KickerInstrumentView;

} ;


namespace gui
{


class KickerInstrumentView : public InstrumentViewFixedSize
{
	Q_OBJECT
public:
	KickerInstrumentView( Instrument * _instrument, QWidget * _parent );
	~KickerInstrumentView() override = default;

private:
	void modelChanged() override;

	Knob * m_startFreqKnob;
	Knob * m_endFreqKnob;
	Knob * m_decayKnob;
	Knob * m_distKnob;
	Knob * m_distEndKnob;
	Knob * m_gainKnob;
	Knob * m_envKnob;
	Knob * m_noiseKnob;
	Knob * m_clickKnob;
	Knob * m_slopeKnob;

	LedCheckBox * m_startNoteToggle;
	LedCheckBox * m_endNoteToggle;

} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_KICKER_H
