// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2006-2008 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 
#include "AutomationTrackView.h"
#include "AutomationClip.h"
#include "AutomationTrack.h"
#include "DeprecationHelper.h"
#include "embed.h"
#include "Engine.h"
#include "ProjectJournal.h"
#include "StringPairDrag.h"
#include "TrackContainerView.h"
#include "TrackLabelButton.h"

namespace noemixerr::gui
{

AutomationTrackView::AutomationTrackView( AutomationTrack * _at, TrackContainerView* tcv ) :
	TrackView( _at, tcv )
{
        setFixedHeight( 32 );
		auto tlb = new TrackLabelButton(this, getTrackSettingsWidget());
		tlb->setIcon(embed::getIconPixmap("automation_track"));
		tlb->move(3, 1);
		tlb->show();
		setModel(_at);
}

void AutomationTrackView::dragEnterEvent( QDragEnterEvent * _dee )
{
	StringPairDrag::processDragEnterEvent( _dee, "automatable_model" );
}




void AutomationTrackView::dropEvent( QDropEvent * _de )
{
	QString type = StringPairDrag::decodeKey( _de );
	QString val = StringPairDrag::decodeValue( _de );
	if( type == "automatable_model" )
	{
		auto mod = dynamic_cast<AutomatableModel*>(Engine::projectJournal()->journallingObject(val.toInt()));
		if( mod != nullptr )
		{
			const int deX = position(_de).x();
			TimePos pos = TimePos(trackContainerView()->currentPosition()
				+ (deX - getTrackContentWidget()->x()) * TimePos::ticksPerBar()
				/ static_cast<int>(trackContainerView()->pixelsPerBar())).toAbsoluteBar();

			if( pos.getTicks() < 0 )
			{
				pos.setTicks( 0 );
			}

			Clip * clip = getTrack()->createClip( pos );
			auto autoClip = dynamic_cast<AutomationClip*>(clip);
			autoClip->addObject( mod );
		}
	}

	update();
}


} // namespace noemixerr::gui
