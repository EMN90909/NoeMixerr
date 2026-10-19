// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_PATTERN_CLIP_VIEW_H
#define NoeMixerr_GUI_PATTERN_CLIP_VIEW_H

#include <QStaticText>

#include "ClipView.h"

namespace noemixerr
{

class PatternClip;

namespace gui
{

class PatternClipView : public ClipView
{
	Q_OBJECT
	Q_PROPERTY(float emptyTrackHeightRatio MEMBER m_emptyTrackHeightRatio)
	Q_PROPERTY(float verticalPadding MEMBER m_verticalPadding)
	Q_PROPERTY(float noteVerticalSpacing MEMBER m_noteVerticalSpacing)
	Q_PROPERTY(float noteHorizontalSpacing MEMBER m_noteHorizontalSpacing)
	Q_PROPERTY(QColor noteColor MEMBER m_noteColor)
public:
	PatternClipView(Clip* clip, TrackView* tv);
	~PatternClipView() override = default;


public slots:
	void update() override;

protected slots:
	void openInPatternEditor();
	void resetName();
	void changeName();


protected:
	void paintEvent( QPaintEvent * pe ) override;
	void mouseDoubleClickEvent( QMouseEvent * _me ) override;
	void constructContextMenu( QMenu * ) override;


private:
	PatternClip* m_patternClip;
	QPixmap m_paintPixmap;
	
	QStaticText m_staticTextName;

	float m_emptyTrackHeightRatio {0.5f};
	float m_verticalPadding {0.15f};
	float m_noteVerticalSpacing {0.2f};
	float m_noteHorizontalSpacing {0.2f};
	QColor m_noteColor {255, 255, 255};
} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_PATTERN_CLIP_VIEW_H
