// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 
#include "PatternClip.h"
 
#include <QDomElement>
 
#include "Engine.h"
#include "PatternClipView.h"
#include "PatternStore.h"
#include "PatternTrack.h"

namespace noemixerr
{


PatternClip::PatternClip(Track* track) :
	Clip(track)
{
	bar_t t = Engine::patternStore()->lengthOfPattern(patternIndex());
	if( t > 0 )
	{
		saveJournallingState( false );
		changeLength( TimePos( t, 0 ) );
		restoreJournallingState();
	}
}

void PatternClip::saveSettings(QDomDocument& doc, QDomElement& element)
{
	element.setAttribute( "name", name() );
	if( element.parentNode().nodeName() == "clipboard" )
	{
		element.setAttribute( "pos", -1 );
	}
	else
	{
		element.setAttribute( "pos", startPosition() );
	}
	element.setAttribute( "len", length() );
	element.setAttribute("off", startTimeOffset());
	element.setAttribute( "muted", isMuted() );
	element.setAttribute("autoresize", QString::number(getAutoResize()));
	if (const auto& c = color())
	{
		element.setAttribute("color", c->name());
	}
}




void PatternClip::loadSettings(const QDomElement& element)
{
	setName( element.attribute( "name" ) );
	if( element.attribute( "pos" ).toInt() >= 0 )
	{
		movePosition( element.attribute( "pos" ).toInt() );
	}
	changeLength( element.attribute( "len" ).toInt() );
	setAutoResize(element.attribute("autoresize", "1").toInt());
	setStartTimeOffset(element.attribute("off").toInt());
	if (static_cast<bool>(element.attribute("muted").toInt()) != isMuted())
	{
		toggleMute();
	}
	
	if (element.hasAttribute("color"))
	{
		if (!element.hasAttribute("usestyle"))
		{
			// for colors saved in 1.3-onwards
			setColor(QColor{element.attribute("color")});
		}
		else if (element.attribute("usestyle").toUInt() == 0)
		{
			// for colors saved before 1.3
			setColor(QColor{element.attribute("color").toUInt()});
		}
	}
}



int PatternClip::patternIndex()
{
	return dynamic_cast<PatternTrack*>(getTrack())->patternIndex();
}



gui::ClipView* PatternClip::createView(gui::TrackView* tv)
{
	return new gui::PatternClipView(this, tv);
}


} // namespace noemixerr
