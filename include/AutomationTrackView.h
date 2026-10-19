// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2006-2008 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_AUTOMATION_TRACK_VIEW_H
#define NoeMixerr_GUI_AUTOMATION_TRACK_VIEW_H

#include "TrackView.h"

namespace noemixerr
{

class AutomationTrack;

namespace gui
{


class AutomationTrackView : public TrackView
{
public:
	AutomationTrackView( AutomationTrack* at, TrackContainerView* tcv );
	~AutomationTrackView() override = default;

	void dragEnterEvent( QDragEnterEvent * _dee ) override;
	void dropEvent( QDropEvent * _de ) override;
} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_AUTOMATION_TRACK_VIEW_H
