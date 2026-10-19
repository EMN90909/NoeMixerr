// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Andreas Brandmaier <andy/at/brandmaier/dot/de>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef BIT_INVADER_H
#define BIT_INVADER_H

#include "AutomatableModel.h"
#include "Instrument.h"
#include "InstrumentView.h"
#include "Graph.h"

namespace noemixerr
{


namespace gui
{
class BitInvaderView;
class Knob;
class LedCheckBox;
class PixmapButton;
}


class BSynth
{
public:
	BSynth( float * sample, NotePlayHandle * _nph,
			bool _interpolation, float factor, 
			const sample_rate_t _sample_rate );
	virtual ~BSynth();
	
	sample_t nextStringSample( float sample_length );


private:
	int sample_index;
	float sample_realindex;
	float* sample_shape;
	NotePlayHandle* nph;
	const sample_rate_t sample_rate;

	bool interpolation;
	
} ;

class BitInvader : public Instrument
{
	Q_OBJECT
public:
	BitInvader(InstrumentTrack * _instrument_track );
	~BitInvader() override = default;

	void playNote( NotePlayHandle * _n,
						SampleFrame* _working_buffer ) override;
	void deleteNotePluginData( NotePlayHandle * _n ) override;


	void saveSettings( QDomDocument & _doc,
							QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;

	QString nodeName() const override;

	float desiredReleaseTimeMs() const override
	{
		return 1.5f;
	}

	gui::PluginView * instantiateView( QWidget * _parent ) override;

protected slots:
	void lengthChanged();
	void samplesChanged( int, int );

	void normalize();


private:
	FloatModel  m_sampleLength;
	graphModel  m_graph;
	
	BoolModel m_interpolation;
	BoolModel m_normalize;
	
	float m_normalizeFactor;
	
	friend class gui::BitInvaderView;
} ;


namespace gui
{

class BitInvaderView : public InstrumentViewFixedSize
{
	Q_OBJECT
public:
	BitInvaderView( Instrument * _instrument,
					QWidget * _parent );

	~BitInvaderView() override = default;

protected slots:
	//void sampleSizeChanged( float _new_sample_length );

	void interpolationToggled( bool value );
	void normalizeToggled( bool value );

	void sinWaveClicked();
	void triangleWaveClicked();
	void sqrWaveClicked();
	void sawWaveClicked();
	void noiseWaveClicked();
	void usrWaveClicked();
	
	void smoothClicked(  );

private:
	void modelChanged() override;

	Knob * m_sampleLengthKnob;
	PixmapButton * m_sinWaveBtn;
	PixmapButton * m_triangleWaveBtn;
	PixmapButton * m_sqrWaveBtn;
	PixmapButton * m_sawWaveBtn;
	PixmapButton * m_whiteNoiseWaveBtn;
	PixmapButton * m_smoothBtn;
	PixmapButton * m_usrWaveBtn;

	static QPixmap * s_artwork;

	Graph * m_graph;
	LedCheckBox * m_interpolationToggle;
	LedCheckBox * m_normalizeToggle;

} ;


} // namespace gui

} // namespace noemixerr

#endif
