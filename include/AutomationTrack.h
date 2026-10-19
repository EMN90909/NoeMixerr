// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2006-2008 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUTOMATION_TRACK_H
#define NoeMixerr_AUTOMATION_TRACK_H

#include "Track.h"

namespace noemixerr
{

class NoeMixerr_EXPORT AutomationTrack : public Track
{
	Q_OBJECT
public:
	AutomationTrack( TrackContainer* tc, bool _hidden = false );
	~AutomationTrack() override = default;

	bool play( const TimePos & _start, const f_cnt_t _frames,
						const f_cnt_t _frame_base, int _clip_num = -1 ) override;

	QString nodeName() const override
	{
		return "automationtrack";
	}

	gui::TrackView * createView( gui::TrackContainerView* ) override;
	Clip* createClip(const TimePos & pos) override;

	void saveTrackSpecificSettings(QDomDocument& doc, QDomElement& parent, bool presetMode) override;
	void loadTrackSpecificSettings( const QDomElement & _this ) override;

private:
	friend class AutomationTrackView;

} ;


} // namespace noemixerr

#endif // NoeMixerr_AUTOMATION_TRACK_H
