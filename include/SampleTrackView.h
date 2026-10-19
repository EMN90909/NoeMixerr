// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SAMPLE_TRACK_VIEW_H
#define NoeMixerr_GUI_SAMPLE_TRACK_VIEW_H


#include "SampleTrack.h"
#include "TrackView.h"

namespace noemixerr
{

namespace gui
{

class Knob;
class MixerChannelLcdSpinBox;
class SampleTrackWindow;
class TrackLabelButton;


class SampleTrackView : public TrackView
{
	Q_OBJECT
public:
	SampleTrackView( SampleTrack* Track, TrackContainerView* tcv );
	~SampleTrackView() override;

	SampleTrackWindow * getSampleTrackWindow()
	{
		return m_window;
	}

	SampleTrack * model()
	{
		return castModel<SampleTrack>();
	}

	const SampleTrack * model() const
	{
		return castModel<SampleTrack>();
	}


	QMenu * createMixerMenu( QString title, QString newMixerLabel ) override;


public slots:
	void showEffects();
	void updateIndicator();


protected:
	void modelChanged() override;
	QString nodeName() const override
	{
		return "SampleTrackView";
	}

	void dragEnterEvent(QDragEnterEvent *dee) override;
	void dropEvent(QDropEvent *de) override;

private slots:
	//! @brief Assign a specific mixer Channel for this track.
	void assignMixerLine(int channelIndex);

	//! @brief Create and assign a new mixer Channel for this track.
	void createMixerLine();
	void corruptStateUpdate();


private:
	SampleTrackWindow * m_window;
	MixerChannelLcdSpinBox* m_mixerChannelNumber;
	Knob * m_volumeKnob;
	Knob * m_panningKnob;
	FadeButton * m_activityIndicator;

	TrackLabelButton * m_tlb;

	FadeButton * getActivityIndicator() override
	{
		return m_activityIndicator;
	}

	friend class SampleTrackWindow;
} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_SAMPLE_TRACK_VIEW_H
