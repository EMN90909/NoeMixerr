// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_FILE_PROCESSOR_VIEW_H
#define NoeMixerr_AUDIO_FILE_PROCESSOR_VIEW_H

#include "InstrumentView.h"


namespace noemixerr
{

namespace gui
{

class AutomatableButtonGroup;
class Knob;
class PixmapButton;
class ComboBox;
class AudioFileProcessorWaveView;


class AudioFileProcessorView : public gui::InstrumentViewFixedSize
{
	Q_OBJECT
public:
	AudioFileProcessorView(Instrument* instrument, QWidget* parent);
	virtual ~AudioFileProcessorView() = default;

	void newWaveView();

protected slots:
	void sampleUpdated();
	void openAudioFile();

protected:
	virtual void dragEnterEvent(QDragEnterEvent* dee);
	virtual void dropEvent(QDropEvent* de);
	virtual void paintEvent(QPaintEvent*);

	// Private methods
private:
	virtual void modelChanged();

	// Private members
private:
	AudioFileProcessorWaveView* m_waveView;
	Knob* m_ampKnob;
	Knob* m_startKnob;
	Knob* m_endKnob;
	Knob* m_loopKnob;

	gui::PixmapButton* m_openAudioFileButton;
	PixmapButton* m_reverseButton;
	AutomatableButtonGroup* m_loopGroup;
	PixmapButton* m_stutterButton;
	ComboBox* m_interpBox;
} ;

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_AUDIO_FILE_PROCESSOR_VIEW_H
