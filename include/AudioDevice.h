// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_DEVICE_H
#define NoeMixerr_AUDIO_DEVICE_H

#include <QMutex>
#include <samplerate.h>

#include "NoeMixerrTypes.h"

class QThread;

namespace noemixerr
{

class AudioEngine;
class AudioBusHandle;
class SampleFrame;


class AudioDevice
{
public:
	AudioDevice( const ch_cnt_t _channels, AudioEngine* audioEngine );
	virtual ~AudioDevice();

	// if audio-driver supports ports, classes inheriting AudioBusHandle
	// (e.g. channel-tracks) can register themselves for making
	// audio-driver able to collect their individual output and provide
	// them at a specific port - currently only supported by JACK
	virtual void registerPort(AudioBusHandle* port);
	virtual void unregisterPort(AudioBusHandle* port);
	virtual void renamePort(AudioBusHandle* port);

	inline bool supportsCapture() const
	{
		return m_supportsCapture;
	}

	inline sample_rate_t sampleRate() const
	{
		return m_sampleRate;
	}

	void startProcessing();

	void stopProcessing();

	bool isRunning() const { return m_running.test(std::memory_order_acquire); }

protected:
	// convert a given audio-buffer to a buffer in signed 16-bit samples
	// returns num of bytes in outbuf
	int convertToS16(const SampleFrame* _ab, const f_cnt_t _frames, int_sample_t* _output_buffer,
		const bool _convert_endian = false);

	// clear given signed-int-16-buffer
	void clearS16Buffer(int_sample_t* _outbuf, const f_cnt_t _frames);

	ch_cnt_t channels() const { return m_channels; }

	AudioEngine* audioEngine() { return m_audioEngine; }

	void setSampleRate(const sample_rate_t _new_sr) { m_sampleRate = _new_sr; }
	void setChannels(const ch_cnt_t channels) { m_channels = channels; }

	static void stopProcessingThread( QThread * thread );
protected:
	bool m_supportsCapture;

private:
	virtual void startProcessingImpl() = 0;
	virtual void stopProcessingImpl() = 0;

	sample_rate_t m_sampleRate;
	ch_cnt_t m_channels;
	AudioEngine* m_audioEngine = nullptr;
	std::atomic_flag m_running = ATOMIC_FLAG_INIT;
};

} // namespace noemixerr

#endif // NoeMixerr_AUDIO_DEVICE_H
