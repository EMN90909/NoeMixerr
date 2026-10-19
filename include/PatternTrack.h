// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PATTERN_TRACK_H
#define NoeMixerr_PATTERN_TRACK_H

#include <QMap>

#include "Track.h"

namespace noemixerr
{

class TrackContainer;

namespace gui
{

class PatternTrackView;

} // namespace gui


/*! Track type used in the Song (Editor) to reference a pattern in the PatternStore */
class NOEMIXERR_EXPORT PatternTrack : public Track
{
	Q_OBJECT
public:
	PatternTrack(TrackContainer* tc);
	~PatternTrack() override;

	bool play( const TimePos & _start, const f_cnt_t _frames,

						const f_cnt_t _frame_base, int _clip_num = -1 ) override;
	gui::TrackView * createView( gui::TrackContainerView* tcv ) override;
	Clip* createClip(const TimePos & pos) override;

	void saveTrackSpecificSettings(QDomDocument& doc, QDomElement& parent, bool presetMode) override;
	void loadTrackSpecificSettings( const QDomElement & _this ) override;

	static PatternTrack* findPatternTrack(int pattern_num);
	static void swapPatternTracks(Track* track1, Track* track2);

	int patternIndex()
	{
		return s_infoMap[this];
	}

	bool automationDisabled( Track * _track )
	{
		return( m_disabledTracks.contains( _track ) );
	}
	void disableAutomation( Track * _track )
	{
		m_disabledTracks.append( _track );
	}
	void enableAutomation( Track * _track )
	{
		m_disabledTracks.removeAll( _track );
	}

protected:
	inline QString nodeName() const override
	{
		return "patterntrack";
	}


private:
	QList<Track *> m_disabledTracks;

	using infoMap = QMap<PatternTrack*, int>;
	static infoMap s_infoMap;

	friend class gui::PatternTrackView;
} ;



} // namespace noemixerr

#endif // NoeMixerr_PATTERN_TRACK_H
