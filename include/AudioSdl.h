// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_SDL_H
#define NoeMixerr_AUDIO_SDL_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_SDL

#include <SDL2/SDL_audio.h>

#include "AudioDevice.h"
#include "AudioDeviceSetupWidget.h"

class QComboBox;

namespace noemixerr
{

class AudioSdl : public AudioDevice
{
public:
	AudioSdl( bool & _success_ful, AudioEngine* audioEngine );
	~AudioSdl() override;

	inline static QString name()
	{
		return QT_TRANSLATE_NOOP( "AudioDeviceSetupWidget",
					"SDL (Simple DirectMedia Layer)" );
	}


	class setupWidget : public gui::AudioDeviceSetupWidget
	{
	public:
		setupWidget( QWidget * _parent );
		~setupWidget() override = default;

		void saveSettings() override;
	
	private:
		void populatePlaybackDeviceComboBox();
		void populateInputDeviceComboBox();

	private:
		QComboBox* m_playbackDeviceComboBox = nullptr;
		QComboBox* m_inputDeviceComboBox = nullptr;

		static QString s_systemDefaultDevice;
	} ;


private:
	void startProcessingImpl() override;
	void stopProcessingImpl() override;

	static void sdlAudioCallback( void * _udata, Uint8 * _buf, int _len );
	void sdlAudioCallback( Uint8 * _buf, int _len );

	static void sdlInputAudioCallback( void * _udata, Uint8 * _buf, int _len );
	void sdlInputAudioCallback( Uint8 * _buf, int _len );

	SDL_AudioSpec m_audioHandle;
	SDL_AudioDeviceID m_outputDevice;

	SDL_AudioSpec m_inputAudioHandle;
	SDL_AudioDeviceID m_inputDevice;
} ;


} // namespace noemixerr

#endif // NoeMixerr_HAVE_SDL

#endif // NoeMixerr_AUDIO_SDL_H
