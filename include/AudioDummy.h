// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_DUMMY_H
#define NoeMixerr_AUDIO_DUMMY_H

#include "AudioDevice.h"
#include "AudioDeviceSetupWidget.h"
#include "AudioEngine.h"
#include "MicroTimer.h"

namespace noemixerr
{

class AudioDummy : public QThread, public AudioDevice
{
	Q_OBJECT
public:
	AudioDummy( bool & _success_ful, AudioEngine* audioEngine ) :
		AudioDevice( DEFAULT_CHANNELS, audioEngine )
	{
		_success_ful = true;
	}

	~AudioDummy() override
	{
		stopProcessing();
	}

	inline static QString name()
	{
		return QT_TRANSLATE_NOOP( "AudioDeviceSetupWidget", "Dummy (no sound output)" );
	}


	class setupWidget : public gui::AudioDeviceSetupWidget
	{
	public:
		setupWidget( QWidget * _parent ) :
			gui::AudioDeviceSetupWidget( AudioDummy::name(), _parent )
		{
		}

		~setupWidget() override = default;

		void saveSettings() override
		{
		}

		void show() override
		{
			parentWidget()->hide();
			QWidget::show();
		}

	} ;


private:
	void startProcessingImpl() override
	{
		start();
	}

	void stopProcessingImpl() override
	{
		stopProcessingThread( this );
	}

	void run() override
	{
		MicroTimer timer;
		while (AudioDevice::isRunning())
		{
			timer.reset();
			audioEngine()->renderNextPeriod();

			const int microseconds = static_cast<int>( audioEngine()->framesPerPeriod() * 1000000.0f / audioEngine()->outputSampleRate() - timer.elapsed() );
			if( microseconds > 0 )
			{
				usleep( microseconds );
			}
		}
	}

} ;

} // namespace noemixerr

#endif // NoeMixerr_AUDIO_DUMMY_H
