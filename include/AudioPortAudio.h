// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Csaba Hruska <csaba.hruska/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_PORTAUDIO_H
#define NoeMixerr_AUDIO_PORTAUDIO_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_PORTAUDIO

#include <QComboBox>
#include <QFormLayout>
#include <QString>
#include <QWidget>
#include <portaudio.h>

#include "AudioDevice.h"
#include "AudioDeviceSetupWidget.h"

namespace noemixerr {

namespace detail {
class PortAudioInitializationGuard
{
public:
	PortAudioInitializationGuard()
		: m_error(Pa_Initialize())
	{
		if (m_error != paNoError) { throw std::runtime_error{"PortAudio: could not initialize"}; }
	}

	~PortAudioInitializationGuard()
	{
		if (m_error == paNoError) { Pa_Terminate(); }
	}

	PortAudioInitializationGuard(const PortAudioInitializationGuard&) = delete;
	PortAudioInitializationGuard(PortAudioInitializationGuard&&) = delete;
	PortAudioInitializationGuard& operator=(const PortAudioInitializationGuard&) = delete;
	PortAudioInitializationGuard& operator=(PortAudioInitializationGuard&&) = delete;

private:
	PaError m_error = paNoError;
};
} // namespace detail

class AudioPortAudio : public AudioDevice
{
public:
	AudioPortAudio(bool& successful, AudioEngine* engine);
	~AudioPortAudio() override;

	AudioPortAudio(const AudioPortAudio&) = delete;
	AudioPortAudio(AudioPortAudio&&) = delete;
	AudioPortAudio& operator=(const AudioPortAudio&) = delete;
	AudioPortAudio& operator=(AudioPortAudio&&) = delete;

	static auto name() -> QString { return QT_TRANSLATE_NOOP("AudioDeviceSetupWidget", "PortAudio"); }

private:
	void startProcessingImpl() override;
	void stopProcessingImpl() override;

	static int processCallback(const void* input, void* output, unsigned long frameCount,
		const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

	detail::PortAudioInitializationGuard m_initGuard;
	PaStream* m_paStream = nullptr;
};
} // namespace noemixerr

namespace noemixerr::gui {
class AudioPortAudioSetupWidget : public AudioDeviceSetupWidget
{
public:
	AudioPortAudioSetupWidget(QWidget* parent);

	void show() override;
	void saveSettings() override;

private:
	class DeviceSelectorWidget;
	QComboBox* m_backendComboBox = nullptr;
	DeviceSelectorWidget* m_inputDevice = nullptr;
	DeviceSelectorWidget* m_outputDevice = nullptr;
};
} // namespace noemixerr::gui

#endif // NoeMixerr_HAVE_PORTAUDIO

#endif // NoeMixerr_AUDIO_PORTAUDIO_H
