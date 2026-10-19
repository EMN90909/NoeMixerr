// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_JACK_H
#define NoeMixerr_AUDIO_JACK_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_JACK
#ifndef NoeMixerr_HAVE_WEAKJACK
#include <jack/jack.h>
#else
#include <weak_libjack.h>
#endif

#include <atomic>
#include <vector>
#ifdef AUDIO_BUS_HANDLE_SUPPORT
#include <QMap>
#endif

#include "AudioDevice.h"
#include "AudioDeviceSetupWidget.h"
#ifdef AUDIO_BUS_HANDLE_SUPPORT
#include "AudioBusHandle.h"
#endif

class QLineEdit;
class QMenu;
class QToolButton;

namespace noemixerr
{

class MidiJack;


class AudioJack : public QObject, public AudioDevice
{
	Q_OBJECT
public:
	AudioJack(bool& successful, AudioEngine* audioEngine);
	~AudioJack() override;

	// this is to allow the jack midi connection to use the same jack client connection
	// the jack callback is handled here, we call the midi client so that it can read
	// it's midi data during the callback
	AudioJack* addMidiClient(MidiJack* midiClient);
	void removeMidiClient() { m_midiClient = nullptr; }
	jack_client_t* jackClient() { return m_client; };

	inline static QString name()
	{
		return QT_TRANSLATE_NOOP("AudioDeviceSetupWidget", "JACK (JACK Audio Connection Kit)");
	}

	class setupWidget : public gui::AudioDeviceSetupWidget
	{
	public:
		setupWidget(QWidget* parent);
		void saveSettings() override;

	private:
		std::vector<std::string> getAudioPortNames(JackPortFlags portFlags) const;
		std::vector<std::string> getAudioInputNames() const;
		std::vector<std::string> getAudioOutputNames() const;
		static QMenu* buildMenu(QToolButton* toolButton, const std::vector<std::string>& names, const QString& filteredNoeMixerrClientName);

	private:
		QLineEdit* m_clientName;
		// Because we do not have access to a JackAudio driver instance we have to be our own client to display inputs and outputs...
		jack_client_t* m_client;

		std::vector<QToolButton*> m_outputDevices;
		std::vector<QToolButton*> m_inputDevices;
	};

private slots:
	void restartAfterZombified();

private:
	bool initJackClient();
	void resizeInputBuffer(jack_nframes_t nframes);

	void startProcessingImpl() override;
	void stopProcessingImpl() override;

	void attemptToConnect(size_t index, const char *noemixerr_port_type, const char *source_port, const char *destination_port);
	void attemptToReconnectOutput(size_t outputIndex, const QString& targetPort);
	void attemptToReconnectInput(size_t inputIndex, const QString& sourcePort);

	void registerPort(AudioBusHandle* port) override;
	void unregisterPort(AudioBusHandle* port) override;
	void renamePort(AudioBusHandle* port) override;

	int processCallback(jack_nframes_t nframes);

	static int staticProcessCallback(jack_nframes_t nframes, void* udata);
	static void shutdownCallback(void* _udata);

	jack_client_t* m_client;

	bool m_active;

	std::atomic<MidiJack*> m_midiClient;
	std::vector<jack_port_t*> m_outputPorts;
	std::vector<jack_port_t*> m_inputPorts;
	jack_default_audio_sample_t** m_tempOutBufs;
	std::vector<SampleFrame> m_inputFrameBuffer;

#ifdef AUDIO_BUS_HANDLE_SUPPORT
	struct StereoPort
	{
		jack_port_t* ports[2];
	};

	using JackPortMap = QMap<AudioBusHandle*, StereoPort>;
	JackPortMap m_portMap;
#endif

signals:
	void zombified();
};

} // namespace noemixerr

#endif // NoeMixerr_HAVE_JACK

#endif // NoeMixerr_AUDIO_JACK_H
