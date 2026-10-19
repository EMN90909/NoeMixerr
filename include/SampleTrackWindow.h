// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SAMPLE_TRACK_WINDOW_H
#define NoeMixerr_GUI_SAMPLE_TRACK_WINDOW_H

#include <QWidget>

#include "ModelView.h"
#include "SampleTrack.h"
#include "SerializingObject.h"

class QLineEdit;

namespace noemixerr::gui
{

class AutomatableButton;
class EffectRackView;
class Knob;
class MixerChannelLcdSpinBox;
class SampleTrackView;


class SampleTrackWindow : public QWidget, public ModelView, public SerializingObjectHook
{
	Q_OBJECT
public:
	SampleTrackWindow(SampleTrackView* stv);
	~SampleTrackWindow() override = default;

	SampleTrack * model()
	{
		return castModel<SampleTrack>();
	}

	const SampleTrack * model() const
	{
		return castModel<SampleTrack>();
	}

	void setSampleTrackView(SampleTrackView * tv);

	SampleTrackView *sampleTrackView()
	{
		return m_stv;
	}


public slots:
	void textChanged(const QString & new_name);
	void toggleVisibility(bool on);
	void updateName();


protected:
	// capture close-events for toggling sample-track-button
	void closeEvent(QCloseEvent* ce) override;

	void saveSettings(QDomDocument & doc, QDomElement & element) override;
	void loadSettings(const QDomElement & element) override;

private:
	void modelChanged() override;

	SampleTrack * m_track;
	SampleTrackView * m_stv;

	// widgets on the top of an sample-track-window
	QLineEdit * m_nameLineEdit;
	Knob * m_volumeKnob;
	Knob * m_panningKnob;
	AutomatableButton* m_muteBtn;
	AutomatableButton* m_soloBtn;
	MixerChannelLcdSpinBox * m_mixerChannelNumber;

	EffectRackView * m_effectRack;
} ;



} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_SAMPLE_TRACK_WINDOW_H
