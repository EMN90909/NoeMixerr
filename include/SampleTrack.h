// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_SAMPLE_TRACK_H
#define NoeMixerr_SAMPLE_TRACK_H

#include "AudioBusHandle.h"
#include "Track.h"


namespace noemixerr
{

namespace gui
{

class SampleTrackView;
class SampleTrackWindow;

} // namespace gui


class SampleTrack : public Track
{
	Q_OBJECT
public:
	SampleTrack( TrackContainer* tc );
	~SampleTrack() override;

	bool play( const TimePos & _start, const f_cnt_t _frames,
						const f_cnt_t _frame_base, int _clip_num = -1 ) override;
	gui::TrackView * createView( gui::TrackContainerView* tcv ) override;
	Clip* createClip(const TimePos & pos) override;


	void saveTrackSpecificSettings(QDomDocument& doc, QDomElement& parent, bool presetMode) override;
	void loadTrackSpecificSettings( const QDomElement & _this ) override;

	inline IntModel * mixerChannelModel()
	{
		return &m_mixerChannelModel;
	}

	inline AudioBusHandle* audioBusHandle()
	{
		return &m_audioBusHandle;
	}

	QString nodeName() const override
	{
		return "sampletrack";
	}

	bool isPlaying()
	{
		return m_isPlaying;
	}

	void setPlaying(bool playing)
	{
		if (m_isPlaying != playing) { emit playingChanged(); }
		m_isPlaying = playing;
	}

signals:
	void playingChanged();

public slots:
	void updateClips();
	void setPlayingClips( bool isPlaying );
	void updateMixerChannel();

private:
	FloatModel m_volumeModel;
	FloatModel m_panningModel;
	IntModel m_mixerChannelModel;
	AudioBusHandle m_audioBusHandle;
	bool m_isPlaying;



	friend class gui::SampleTrackView;
	friend class gui::SampleTrackWindow;

} ;


} // namespace noemixerr

#endif // NoeMixerr_SAMPLE_TRACK_H
