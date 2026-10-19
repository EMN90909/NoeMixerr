// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_AUTOMATION_CLIP_VIEW_H
#define NoeMixerr_GUI_AUTOMATION_CLIP_VIEW_H

#include <QStaticText>

#include "ClipView.h"

namespace noemixerr
{

class AutomationClip;

namespace gui
{


class AutomationClipView : public ClipView
{
	Q_OBJECT


public:
	AutomationClipView( AutomationClip * _clip, TrackView * _parent );
	~AutomationClipView() override = default;

public slots:
	/// Opens this view's clip in the global automation editor
	void openInAutomationEditor();
	void update() override;


protected slots:
	void resetName();
	void changeName();
	void disconnectObject( QAction * _a );
	void toggleRecording();
	void flipY();
	void flipX();

protected:
	void constructContextMenu( QMenu * ) override;
	void mouseDoubleClickEvent(QMouseEvent * me ) override;
	void paintEvent( QPaintEvent * pe ) override;
	void dragEnterEvent( QDragEnterEvent * _dee ) override;
	void dropEvent( QDropEvent * _de ) override;


private:
	AutomationClip * m_clip;
	QPixmap m_paintPixmap;
	
	QStaticText m_staticTextName;

	//! @brief Preserves the auto points over different scale
	void scaleTimemapToFit( float oldMin, float oldMax );
	
	bool isResizableBeforeStart() override { return false; }
} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_AUTOMATION_CLIP_VIEW_H
