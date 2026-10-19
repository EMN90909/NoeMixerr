// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 
#include "PatternTrackView.h"

#include "Engine.h"
#include "GuiApplication.h"
#include "MainWindow.h"
#include "PatternEditor.h"
#include "PatternStore.h"
#include "PatternTrack.h"
#include "TrackLabelButton.h"

namespace noemixerr::gui
{

PatternTrackView::PatternTrackView(PatternTrack* pt, TrackContainerView* tcv) :
	TrackView(pt, tcv),
	m_patternTrack(pt)
{
	setFixedHeight( 32 );
	// drag'n'drop with pattern tracks only causes troubles (and makes no sense too), so disable it
	setAcceptDrops( false );

	m_trackLabel = new TrackLabelButton( this, getTrackSettingsWidget() );
	m_trackLabel->setIcon( embed::getIconPixmap("pattern_track"));
	m_trackLabel->move( 3, 1 );
	m_trackLabel->show();
	connect( m_trackLabel, SIGNAL(clicked(bool)),
			this, SLOT(clickedTrackLabel()));
	setModel(pt);
}




PatternTrackView::~PatternTrackView()
{
	getGUI()->patternEditor()->m_editor->removeViewsForPattern(PatternTrack::s_infoMap[m_patternTrack]);
}




bool PatternTrackView::close()
{
	getGUI()->patternEditor()->m_editor->removeViewsForPattern(PatternTrack::s_infoMap[m_patternTrack]);
	return TrackView::close();
}




void PatternTrackView::clickedTrackLabel()
{
	Engine::patternStore()->setCurrentPattern(m_patternTrack->patternIndex());
	getGUI()->mainWindow()->togglePatternEditorWin(true);
}


} // namespace noemixerr::gui
