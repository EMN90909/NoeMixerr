// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SONG_EDITOR_H
#define NoeMixerr_GUI_SONG_EDITOR_H

#include "Editor.h"
#include "TrackContainerView.h"

class QLabel;
class QScrollBar;

namespace noemixerr
{

class IntModel;
class Song;
class ComboBoxModel;

namespace gui
{


class ActionGroup;
class AutomatableSlider;
class ComboBox;
class LcdSpinBox;
class MeterDialog;
class PositionLine;
class TextFloat;
class TimeLineWidget;


class SongEditor : public TrackContainerView
{
	Q_OBJECT
public:
	enum class EditMode
	{
		Draw,
		Knife,
		Select
	};

	SongEditor( Song * song );
	~SongEditor() override;

	void saveSettings( QDomDocument& doc, QDomElement& element ) override;
	void loadSettings( const QDomElement& element ) override;

	ComboBoxModel* snappingModel() const;

	//! @brief Return grid size as number of bars
	float getSnapSize() const;

	QString getSnapSizeString() const;

	TimeLineWidget* timeLine() const { return m_timeLine; }
	PositionLine* positionLine() const { return m_positionLine; }

public slots:
	void scrolled( int new_pos );
	void selectRegionFromPixels(int xStart, int xEnd);
	void stopSelectRegion();
	void updateRubberband();

	void setEditMode( noemixerr::gui::SongEditor::EditMode mode );
	void setEditModeDraw();
	void setEditModeKnife();
	void setEditModeSelect();
	void toggleProportionalSnap();

	void updatePosition();
	void updatePositionLine();
	void selectAllClips( bool select );

protected:
	void mousePressEvent(QMouseEvent * me) override;
	void mouseMoveEvent(QMouseEvent * me) override;
	void mouseReleaseEvent(QMouseEvent * me) override;

private slots:
	void setMasterVolume( int new_val );
	void showMasterVolumeFloat();
	void updateMasterVolumeFloat( int new_val );
	void hideMasterVolumeFloat();

	void setMasterPitch( int new_val );
	void showMasterPitchFloat();
	void updateMasterPitchFloat( int new_val );
	void hideMasterPitchFloat();

	void updateScrollBar(int len);

	void zoomingChanged();

private:
	void keyPressEvent( QKeyEvent * ke ) override;
	void wheelEvent( QWheelEvent * we ) override;

	bool allowRubberband() const override;
	bool knifeMode() const override;

	//! @brief Convert zoom slider's value to bar width in pixels
	int calculatePixelsPerBar() const;

	//! @brief Convert bar width in pixels to zoom slider value
	int calculateZoomSliderValue(int pixelsPerBar) const;

	int trackIndexFromSelectionPoint(int yPos);
	int indexOfTrackView(const TrackView* tv);

	Song * m_song;

	QScrollBar * m_leftRightScroll;

	void adjustLeftRightScoll(int value);

	LcdSpinBox * m_tempoSpinBox;

	TimeLineWidget* m_timeLine;
	PositionLine* m_positionLine;

	MeterDialog * m_timeSigDisplay;
	AutomatableSlider * m_masterVolumeSlider;
	AutomatableSlider * m_masterPitchSlider;

	TextFloat * m_mvsStatus;
	TextFloat * m_mpsStatus;


	IntModel* m_zoomingModel;
	ComboBoxModel* m_snappingModel;
	bool m_proportionalSnap;

	bool m_scrollBack;
	bool m_smoothScroll;

	EditMode m_mode;
	EditMode m_ctrlMode; //!< Mode they were in before they hit ctrl

	QPoint m_origin;
	QPoint m_scrollPos;
	QPoint m_mousePos;
	int m_rubberBandStartTrackview;
	TimePos m_rubberbandStartTimePos;
	int m_rubberbandPixelsPerBar; //!< Pixels per bar when selection starts
	int m_trackHeadWidth;
	bool m_selectRegion;

	friend class SongEditorWindow;

signals:
	void pixelsPerBarChanged(float);
	void proportionalSnapChanged();
} ;




class SongEditorWindow : public Editor
{
	Q_OBJECT
public:
	SongEditorWindow( Song* song );

	QSize sizeHint() const override;

	SongEditor* m_editor;
	void syncEditMode();

protected:
	void resizeEvent( QResizeEvent * event ) override;
	void changeEvent( QEvent * ) override;

protected slots:
	void play() override;
	void record() override;
	void recordAccompany() override;
	void stop() override;

	void lostFocus();
	void adjustUiAfterProjectLoad();

	void updateSnapLabel();

signals:
	void playTriggered();
	void resized();

private:
	QAction* m_addPatternTrackAction;
	QAction* m_addSampleTrackAction;
	QAction* m_addAutomationTrackAction;
	QAction* m_setProportionalSnapAction;

	ActionGroup * m_editModeGroup;
	QAction* m_drawModeAction;
	QAction* m_knifeModeAction;
	QAction* m_selectModeAction;
	QAction* m_crtlAction;

	AutomatableSlider * m_zoomingSlider;
	ComboBox * m_snappingComboBox;
	QLabel* m_snapSizeLabel;

	QAction* m_insertBarAction;
	QAction* m_removeBarAction;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_SONG_EDITOR_H
