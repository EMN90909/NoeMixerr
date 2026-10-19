// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _TRIPLE_OSCILLATOR_H
#define _TRIPLE_OSCILLATOR_H

#include <memory>

#include "Instrument.h"
#include "InstrumentView.h"
#include "AutomatableModel.h"
#include "OscillatorConstants.h"
#include "SampleBuffer.h"

namespace noemixerr
{


class NotePlayHandle;  // IWYU pragma: keep
class Oscillator;


namespace gui
{
class AutomatableButtonGroup;
class Knob;
class PixmapButton;
class TripleOscillatorView;
} // namespace gui


const int NUM_OF_OSCILLATORS = 3;


class OscillatorObject : public Model
{
	Q_OBJECT
public:
	OscillatorObject( Model * _parent, int _idx );
private:
	FloatModel m_volumeModel;
	FloatModel m_panModel;
	FloatModel m_coarseModel;
	FloatModel m_fineLeftModel;
	FloatModel m_fineRightModel;
	FloatModel m_phaseOffsetModel;
	FloatModel m_stereoPhaseDetuningModel;
	IntModel m_waveShapeModel;
	IntModel m_modulationAlgoModel;
	BoolModel m_useWaveTableModel;
	std::shared_ptr<const SampleBuffer> m_sampleBuffer = SampleBuffer::emptyBuffer();
	std::shared_ptr<const OscillatorConstants::waveform_t> m_userAntiAliasWaveTable;

	float m_volumeLeft;
	float m_volumeRight;

	// normalized detuning -> x/sampleRate
	float m_detuningLeft;
	float m_detuningRight;
	// normalized offset -> x/360
	float m_phaseOffsetLeft;
	float m_phaseOffsetRight;
	bool m_useWaveTable;

	friend class TripleOscillator;
	friend class gui::TripleOscillatorView;


private slots:
	void oscUserDefWaveDblClick();

	void updateVolume();
	void updateDetuningLeft();
	void updateDetuningRight();
	void updatePhaseOffsetLeft();
	void updatePhaseOffsetRight();
	void updateUseWaveTable();

} ;




class TripleOscillator : public Instrument
{
	Q_OBJECT
public:
	TripleOscillator( InstrumentTrack * _track );
	~TripleOscillator() override = default;

	void playNote( NotePlayHandle * _n,
						SampleFrame* _working_buffer ) override;
	void deleteNotePluginData( NotePlayHandle * _n ) override;


	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;

	QString nodeName() const override;

	float desiredReleaseTimeMs() const override
	{
		return 3.f;
	}

	gui::PluginView* instantiateView( QWidget * _parent ) override;


protected slots:
	void updateAllDetuning();


private:
	OscillatorObject * m_osc[NUM_OF_OSCILLATORS];

	struct oscPtr
	{
		Oscillator * oscLeft;
		Oscillator * oscRight;
	} ;


	friend class gui::TripleOscillatorView;

} ;


namespace gui
{


class TripleOscillatorView : public InstrumentViewFixedSize
{
	Q_OBJECT
public:
	TripleOscillatorView( Instrument * _instrument, QWidget * _parent );
	~TripleOscillatorView() override = default;


private:
	void modelChanged() override;

	AutomatableButtonGroup * m_mod1BtnGrp;
	AutomatableButtonGroup * m_mod2BtnGrp;

	struct OscillatorKnobs
	{
		OscillatorKnobs( Knob * v,
					Knob * p,
					Knob * c,
					Knob * fl,
					Knob * fr,
					Knob * po,
					Knob * spd,
					PixmapButton * uwb,
					AutomatableButtonGroup * wsbg,
					PixmapButton * wt) :
			m_volKnob( v ),
			m_panKnob( p ),
			m_coarseKnob( c ),
			m_fineLeftKnob( fl ),
			m_fineRightKnob( fr ),
			m_phaseOffsetKnob( po ),
			m_stereoPhaseDetuningKnob( spd ),
			m_userWaveButton( uwb ),
			m_waveShapeBtnGrp( wsbg ),
			m_multiBandWaveTableButton( wt )
		{
		}
		OscillatorKnobs() = default;
		Knob * m_volKnob;
		Knob * m_panKnob;
		Knob * m_coarseKnob;
		Knob * m_fineLeftKnob;
		Knob * m_fineRightKnob;
		Knob * m_phaseOffsetKnob;
		Knob * m_stereoPhaseDetuningKnob;
		PixmapButton * m_userWaveButton;
		AutomatableButtonGroup * m_waveShapeBtnGrp;
		PixmapButton * m_multiBandWaveTableButton;

	} ;

	OscillatorKnobs m_oscKnobs[NUM_OF_OSCILLATORS];
} ;


} // namespace gui

} // namespace noemixerr

#endif
