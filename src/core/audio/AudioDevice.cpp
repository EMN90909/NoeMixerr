// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <cstring>

#include "AudioDevice.h"
#include "AudioEngine.h"

namespace noemixerr
{

AudioDevice::AudioDevice(const ch_cnt_t _channels, AudioEngine* _audioEngine)
	: m_supportsCapture(false)
	, m_sampleRate(_audioEngine->outputSampleRate())
	, m_channels(_channels)
	, m_audioEngine(_audioEngine)
{
}



AudioDevice::~AudioDevice()
{
	assert(!isRunning() && "device should have been stopped before being destroyed");
}

void AudioDevice::startProcessing()
{
	m_running.test_and_set(std::memory_order_acquire);
	startProcessingImpl();
}

void AudioDevice::stopProcessing()
{
	m_running.clear(std::memory_order_release);
	stopProcessingImpl();
}

void AudioDevice::stopProcessingThread( QThread * thread )
{
	if( !thread->wait( 30000 ) )
	{
		fprintf( stderr, "Terminating audio device thread\n" );
		thread->terminate();
		if( !thread->wait( 1000 ) )
		{
			fprintf( stderr, "Thread not terminated yet\n" );
		}
	}
}



void AudioDevice::registerPort(AudioBusHandle*)
{
}




void AudioDevice::unregisterPort(AudioBusHandle*)
{
}




void AudioDevice::renamePort(AudioBusHandle*)
{
}

int AudioDevice::convertToS16(const SampleFrame* _ab,
								const f_cnt_t _frames,
								int_sample_t * _output_buffer,
								const bool _convert_endian )
{
	if( _convert_endian )
	{
		for( f_cnt_t frame = 0; frame < _frames; ++frame )
		{
			for( ch_cnt_t chnl = 0; chnl < channels(); ++chnl )
			{
				auto temp = static_cast<int_sample_t>(AudioEngine::clip(_ab[frame][chnl]) * OUTPUT_SAMPLE_MULTIPLIER);

				( _output_buffer + frame * channels() )[chnl] =
						( temp & 0x00ff ) << 8 |
						( temp & 0xff00 ) >> 8;
			}
		}
	}
	else
	{
		for( f_cnt_t frame = 0; frame < _frames; ++frame )
		{
			for( ch_cnt_t chnl = 0; chnl < channels(); ++chnl )
			{
				(_output_buffer + frame * channels())[chnl]
					= static_cast<int_sample_t>(AudioEngine::clip(_ab[frame][chnl]) * OUTPUT_SAMPLE_MULTIPLIER);
			}
		}
	}

	return _frames * channels() * BYTES_PER_INT_SAMPLE;
}




void AudioDevice::clearS16Buffer( int_sample_t * _outbuf, const f_cnt_t _frames )
{

	assert( _outbuf != nullptr );

	memset( _outbuf, 0,  _frames * channels() * BYTES_PER_INT_SAMPLE );
}

} // namespace noemixerr
