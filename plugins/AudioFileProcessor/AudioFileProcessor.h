// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_FILE_PROCESSOR_H
#define NoeMixerr_AUDIO_FILE_PROCESSOR_H


#include "AutomatableModel.h"
#include "ComboBoxModel.h"

#include "Instrument.h"
#include "Sample.h"
#include "NoeMixerrTypes.h"


namespace noemixerr
{

class AudioFileProcessor : public Instrument
{
	Q_OBJECT
public:
	AudioFileProcessor( InstrumentTrack * _instrument_track );

	void playNote( NotePlayHandle * _n,
						SampleFrame* _working_buffer ) override;
	void deleteNotePluginData( NotePlayHandle * _n ) override;

	void saveSettings(QDomDocument& doc, QDomElement& elem) override;
	void loadSettings(const QDomElement& elem) override;

	void loadFile( const QString & _file ) override;

	QString nodeName() const override;

	auto beatLen(NotePlayHandle* note) const -> f_cnt_t override;

	float desiredReleaseTimeMs() const override
	{
		return 3.f;
	}

	gui::PluginView* instantiateView( QWidget * _parent ) override;

	Sample const & sample() const { return m_sample; }

	FloatModel & ampModel() { return m_ampModel; }
	FloatModel & startPointModel() { return m_startPointModel; }
	FloatModel & endPointModel() { return m_endPointModel; }
	FloatModel & loopPointModel() { return m_loopPointModel; }
	BoolModel & reverseModel() { return m_reverseModel; }
	IntModel & loopModel() { return m_loopModel; }
	BoolModel & stutterModel() { return m_stutterModel; }
	ComboBoxModel & interpolationModel() { return m_interpolationModel; }


public slots:
	void setAudioFile(const QString& _audio_file, bool _rename = true);

private slots:
	void reverseModelChanged();
	void ampModelChanged();
	void loopPointChanged();
	void startPointChanged();
	void endPointChanged();
	void pointChanged();
	void stutterModelChanged();


signals:
	void isPlaying( noemixerr::f_cnt_t _current_frame );
	void sampleUpdated();

private:
	Sample m_sample;

	FloatModel m_ampModel;
	FloatModel m_startPointModel;
	FloatModel m_endPointModel;
	FloatModel m_loopPointModel;
	BoolModel m_reverseModel;
	IntModel m_loopModel;
	BoolModel m_stutterModel;
	ComboBoxModel m_interpolationModel;

	f_cnt_t m_nextPlayStartPoint;
	bool m_nextPlayBackwards;
} ;

} // namespace noemixerr

#endif // NoeMixerr_AUDIO_FILE_PROCESSOR_H
