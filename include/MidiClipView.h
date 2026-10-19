// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_MIDI_CLIP_VIEW_H
#define NoeMixerr_GUI_MIDI_CLIP_VIEW_H

#include <QStaticText>
#include "ClipView.h"
#include "embed.h"

namespace noemixerr
{

class MidiClip;

namespace gui
{


class MidiClipView : public ClipView
{
	Q_OBJECT

public:
	MidiClipView( MidiClip* clip, TrackView* parent );
	~MidiClipView() override = default;

	Q_PROPERTY(QColor noteFillColor READ getNoteFillColor WRITE setNoteFillColor)
	Q_PROPERTY(QColor noteBorderColor READ getNoteBorderColor WRITE setNoteBorderColor)
	Q_PROPERTY(QColor mutedNoteFillColor READ getMutedNoteFillColor WRITE setMutedNoteFillColor)
	Q_PROPERTY(QColor mutedNoteBorderColor READ getMutedNoteBorderColor WRITE setMutedNoteBorderColor)

	QColor const & getNoteFillColor() const { return m_noteFillColor; }
	void setNoteFillColor(QColor const & color) { m_noteFillColor = color; }

	QColor const & getNoteBorderColor() const { return m_noteBorderColor; }
	void setNoteBorderColor(QColor const & color) { m_noteBorderColor = color; }

	QColor const & getMutedNoteFillColor() const { return m_mutedNoteFillColor; }
	void setMutedNoteFillColor(QColor const & color) { m_mutedNoteFillColor = color; }

	QColor const & getMutedNoteBorderColor() const { return m_mutedNoteBorderColor; }
	void setMutedNoteBorderColor(QColor const & color) { m_mutedNoteBorderColor = color; }

	// Returns true if selection can be merged and false if not
	static bool canMergeSelection(QVector<ClipView*> clipvs);
	static void mergeClips(QVector<ClipView*> clipvs);
	static void bulkClearNotesOutOfBounds(QVector<ClipView*> clipvs);

public slots:
	noemixerr::MidiClip* getMidiClip();
	void update() override;


protected slots:
	void openInPianoRoll();
	void setGhostInPianoRoll();
	void setGhostInAutomationEditor();

	void resetName();
	void changeName();
	void transposeSelection();
	void clearNotesOutOfBounds();


protected:
	void constructContextMenu( QMenu * ) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void mouseDoubleClickEvent( QMouseEvent * _me ) override;
	void paintEvent( QPaintEvent * pe ) override;
	void wheelEvent( QWheelEvent * _we ) override;


private:
	QPixmap m_stepBtnOn0 = embed::getIconPixmap("step_btn_on_0");
	QPixmap m_stepBtnOn200 = embed::getIconPixmap("step_btn_on_200");
	QPixmap m_stepBtnOff = embed::getIconPixmap("step_btn_off");
	QPixmap m_stepBtnOffLight = embed::getIconPixmap("step_btn_off_light");
	QPixmap m_stepBtnHighlight = embed::getIconPixmap("step_btn_highlight");

	MidiClip* m_clip;
	QPixmap m_paintPixmap;

	QColor m_noteFillColor;
	QColor m_noteBorderColor;
	QColor m_mutedNoteFillColor;
	QColor m_mutedNoteBorderColor;

	QStaticText m_staticTextName;

	bool m_legacySEPattern;

	bool isResizableBeforeStart() override { return false; }
	
	bool destructiveSplitClip(const TimePos pos) override;
} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_MIDI_CLIP_VIEW_H
