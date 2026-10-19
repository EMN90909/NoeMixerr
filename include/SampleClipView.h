// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SAMPLE_CLIP_VIEW_H
#define NoeMixerr_GUI_SAMPLE_CLIP_VIEW_H

#include "ClipView.h"

#include "SampleThumbnail.h"

namespace noemixerr
{

class SampleClip;

namespace gui
{


class SampleClipView : public ClipView
{
	Q_OBJECT

public:
	SampleClipView( SampleClip * _clip, TrackView * _tv );
	~SampleClipView() override = default;

public slots:
	void updateSample();
	void reverseSample();
	void setAutomationGhost();



protected:
	void constructContextMenu(QMenu* cm) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void mouseReleaseEvent( QMouseEvent * _me ) override;
	void dragEnterEvent( QDragEnterEvent * _dee ) override;
	void dropEvent( QDropEvent * _de ) override;
	void mouseDoubleClickEvent( QMouseEvent * ) override;
	void paintEvent( QPaintEvent * ) override;


private:
	SampleClip * m_clip;
	SampleThumbnail m_sampleThumbnail;
	QPixmap m_paintPixmap;
	long m_paintPixmapXPosition;
} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_SAMPLE_CLIP_VIEW_H
