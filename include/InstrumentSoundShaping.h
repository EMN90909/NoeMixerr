// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_INSTRUMENT_SOUND_SHAPING_H
#define NoeMixerr_INSTRUMENT_SOUND_SHAPING_H

#include "ComboBoxModel.h"
#include "EnvelopeAndLfoParameters.h"

namespace noemixerr
{


class InstrumentTrack;
class NotePlayHandle;
class SampleFrame;

namespace gui
{
class InstrumentSoundShapingView;
}


class InstrumentSoundShaping : public Model, public JournallingObject
{
	Q_OBJECT
public:
	InstrumentSoundShaping( InstrumentTrack * _instrument_track );
	~InstrumentSoundShaping() override = default;

	void processAudioBuffer( SampleFrame* _ab, const f_cnt_t _frames,
							NotePlayHandle * _n );

	const EnvelopeAndLfoParameters& getVolumeParameters() const { return m_volumeParameters; }
	EnvelopeAndLfoParameters& getVolumeParameters() { return m_volumeParameters; }

	const EnvelopeAndLfoParameters& getCutoffParameters() const { return m_cutoffParameters; }
	EnvelopeAndLfoParameters& getCutoffParameters() { return m_cutoffParameters; }

	const EnvelopeAndLfoParameters& getResonanceParameters() const { return m_resonanceParameters; }
	EnvelopeAndLfoParameters& getResonanceParameters() { return m_resonanceParameters; }

	BoolModel& getFilterEnabledModel() { return m_filterEnabledModel; }
	ComboBoxModel& getFilterModel() { return m_filterModel; }
	FloatModel& getFilterCutModel() { return m_filterCutModel; }
	FloatModel& getFilterResModel() { return m_filterResModel; }

	f_cnt_t envFrames( const bool _only_vol = false ) const;
	f_cnt_t releaseFrames() const;

	float volumeLevel( NotePlayHandle * _n, const f_cnt_t _frame );


	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "eldata";
	}

private:
	QString getVolumeNodeName() const;
	QString getCutoffNodeName() const;
	QString getResonanceNodeName() const;

private:
	InstrumentTrack * m_instrumentTrack;

	EnvelopeAndLfoParameters m_volumeParameters;
	EnvelopeAndLfoParameters m_cutoffParameters;
	EnvelopeAndLfoParameters m_resonanceParameters;

	BoolModel m_filterEnabledModel;
	ComboBoxModel m_filterModel;
	FloatModel m_filterCutModel;
	FloatModel m_filterResModel;
};


} // namespace noemixerr

#endif // NoeMixerr_INSTRUMENT_SOUND_SHAPING_H
