// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2006-2008 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "AutomationTrack.h"

#include "AutomationTrackView.h"
#include "AutomationClip.h"

namespace noemixerr
{


AutomationTrack::AutomationTrack( TrackContainer* tc, bool _hidden ) :
	Track( _hidden ? Type::HiddenAutomation : Type::Automation, tc )
{
	setName( tr( "Automation track" ) );
}

bool AutomationTrack::play( const TimePos & time_start, const f_cnt_t _frames,
							const f_cnt_t _frame_base, int _clip_num )
{
	return false;
}




gui::TrackView* AutomationTrack::createView( gui::TrackContainerView* tcv )
{
	return new gui::AutomationTrackView( this, tcv );
}




Clip* AutomationTrack::createClip(const TimePos & pos)
{
	auto p = new AutomationClip(this);
	p->movePosition(pos);
	return p;
}




void AutomationTrack::saveTrackSpecificSettings(QDomDocument& doc, QDomElement& _this, bool presetMode)
{
}




void AutomationTrack::loadTrackSpecificSettings( const QDomElement & _this )
{
	// just in case something somehow wrent wrong...
	if( type() == Type::HiddenAutomation )
	{
		setMuted( false );
	}
}


} // namespace noemixerr
