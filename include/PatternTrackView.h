// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_PATTERN_TRACK_VIEW_H
#define NoeMixerr_GUI_PATTERN_TRACK_VIEW_H

#include "TrackView.h"

namespace noemixerr
{

class PatternTrack;

namespace gui
{

class TrackLabelButton;


class PatternTrackView : public TrackView
{
	Q_OBJECT
public:
	PatternTrackView(PatternTrack* pt, TrackContainerView* tcv);
	~PatternTrackView() override;

	bool close() override;

	const PatternTrack* getPatternTrack() const
	{
		return (m_patternTrack);
	}


public slots:
	void clickedTrackLabel();


private:
	PatternTrack* m_patternTrack;
	TrackLabelButton * m_trackLabel;
} ;



} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_PATTERN_TRACK_VIEW_H
