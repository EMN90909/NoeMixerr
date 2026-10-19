// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TRACK_OPERATIONS_WIDGET_H
#define NoeMixerr_GUI_TRACK_OPERATIONS_WIDGET_H

#include <QWidget>

class QPushButton;

namespace noemixerr::gui
{

class AutomatableButton;
class TrackGrip;
class TrackView;

//! @brief The grip and the mute/solo buttons of a track.
class TrackOperationsWidget : public QWidget
{
	Q_OBJECT
public:

	//! @brief Create a new TrackOperationsWidget
	//! @param parent The TrackView to contain this widget
	TrackOperationsWidget(TrackView* parent);

	~TrackOperationsWidget() override = default;

	TrackGrip* getTrackGrip() const { return m_trackGrip; }

protected:
	//! @brief Repaint the trackOperationsWidget
	//!
	//! Only things that's done for now is to paint the background with the brush of the window from the palette.
	void paintEvent(QPaintEvent* pe) override;

	//! @brief Show a message box warning the user that this track is about to be closed
	bool confirmRemoval();


private slots:
	void cloneTrack();  //!< Clone this track
	void removeTrack(); //!< Remove this track from the track list

	//! @brief Update the trackOperationsWidget context menu
	//!
	//! For all track types, we have the Clone and Remove options.
	//! For instrument-tracks we also offer the MIDI-control-menu
	//! For automation tracks, extra options: turn on/off recording on all Clips (same should be added for sample tracks
	//! when sampletrack recording is implemented)
	void updateMenu();

	void selectTrackColor();
	void randomizeTrackColor();
	void resetTrackColor();
	void resetClipColors();
	void toggleRecording(bool on);
	void recordingOn();
	void recordingOff();
	void clearTrack(); //!< Clears all Clips from the track

private:
	TrackView * m_trackView;

	TrackGrip* m_trackGrip;
	QPushButton * m_trackOps;
	AutomatableButton* m_muteBtn;
	AutomatableButton* m_soloBtn;

	friend class TrackView;

signals:
	void trackRemovalScheduled( noemixerr::gui::TrackView * t );
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TRACK_OPERATIONS_WIDGET_H
