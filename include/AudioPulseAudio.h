// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_PULSEAUDIO_H
#define NoeMixerr_AUDIO_PULSEAUDIO_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_PULSEAUDIO

#include <pulse/pulseaudio.h>
#include <QSemaphore>
#include <QThread>

#include "AudioDevice.h"
#include "AudioDeviceSetupWidget.h"

class QLineEdit;

namespace noemixerr
{

namespace gui
{
class LcdSpinBox;
}


class AudioPulseAudio : public QThread, public AudioDevice
{
	Q_OBJECT
public:
	AudioPulseAudio( bool & _success_ful, AudioEngine* audioEngine );

	inline static QString name()
	{
		return QT_TRANSLATE_NOOP( "AudioDeviceSetupWidget", "PulseAudio" );
	}

	static QString probeDevice();


	class setupWidget : public gui::AudioDeviceSetupWidget
	{
	public:
		setupWidget( QWidget * _parent );
		~setupWidget() override;

		void saveSettings() override;

	private:
		QLineEdit * m_device;
		gui::LcdSpinBox * m_channels;

	} ;


	void streamWriteCallback( pa_stream * s, size_t length );

	void signalConnected( bool connected );

	pa_stream * m_s;
	pa_sample_spec m_sampleSpec;
	double m_latency;

private:
	void startProcessingImpl() override;
	void stopProcessingImpl() override;
	void run() override;

	bool m_connected;
	QSemaphore m_connectedSemaphore;

} ;

} // namespace noemixerr

#endif // NoeMixerr_HAVE_PULSEAUDIO

#endif // NoeMixerr_AUDIO_PULSEAUDIO_H
