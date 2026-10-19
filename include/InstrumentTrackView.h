// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_INSTRUMENT_TRACK_VIEW_H
#define NoeMixerr_GUI_INSTRUMENT_TRACK_VIEW_H

#include "TrackView.h"

#include "InstrumentTrack.h"


namespace noemixerr::gui
{


class InstrumentTrackWindow;
class Knob;
class MidiCCRackView;
class MixerChannelLcdSpinBox;
class TrackContainerView;
class TrackLabelButton;


class InstrumentTrackView : public TrackView
{
	Q_OBJECT
public:
	InstrumentTrackView( InstrumentTrack * _it, TrackContainerView* tc );
	~InstrumentTrackView() override;

	InstrumentTrackWindow * getInstrumentTrackWindow();

	InstrumentTrack * model()
	{
		return castModel<InstrumentTrack>();
	}

	const InstrumentTrack * model() const
	{
		return castModel<InstrumentTrack>();
	}

	static InstrumentTrackWindow * topLevelInstrumentTrackWindow();

	QMenu * midiMenu()
	{
		return m_midiMenu;
	}

	// Create a menu for assigning/creating channels for this track
	QMenu * createMixerMenu( QString title, QString newMixerLabel ) override;


protected:
	void modelChanged() override;
	void dragEnterEvent( QDragEnterEvent * _dee ) override;
	void dropEvent( QDropEvent * _de ) override;


private slots:
	void onInstrumentChanged();
	void toggleInstrumentWindow( bool _on );
	void toggleMidiCCRack();
	void activityIndicatorPressed();
	void activityIndicatorReleased();

	void midiInSelected();
	void midiOutSelected();
	void midiConfigChanged();

	//! @brief Assign a specific mixer Channel for this track
	void assignMixerLine(int channelIndex);

	//! @brief Create and assign a new mixer Channel for this track
	void createMixerLine();

	void handleConfigChange(QString cls, QString attr, QString value);
	
	void corruptStateUpdate();

private:
	static QPixmap determinePixmap(InstrumentTrack* instrumentTrack);

private:
	InstrumentTrackWindow * m_window;

	// widgets in track-settings-widget
	TrackLabelButton * m_tlb;
	MixerChannelLcdSpinBox* m_mixerChannelNumber;
	Knob * m_volumeKnob;
	Knob * m_panningKnob;
	FadeButton * m_activityIndicator;

	QMenu * m_midiMenu;

	QAction * m_midiInputAction;
	QAction * m_midiOutputAction;

	std::unique_ptr<MidiCCRackView> m_midiCCRackView;

	QPoint m_lastPos;

	FadeButton * getActivityIndicator() override
	{
		return m_activityIndicator;
	}

	friend class InstrumentTrackWindow;
} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_INSTRUMENT_TRACK_VIEW_H
