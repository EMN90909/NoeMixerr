// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2013 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "AudioFileWave.h"
#include "endian_handling.h"
#include "AudioEngine.h"


namespace noemixerr
{

AudioFileWave::AudioFileWave( OutputSettings const & outputSettings,
				const ch_cnt_t channels, bool & successful,
				const QString & file,
				AudioEngine* audioEngine ) :
	AudioFileDevice( outputSettings, channels, file, audioEngine ),
	m_sf( nullptr )
{
	successful = outputFileOpened() && startEncoding();
}




AudioFileWave::~AudioFileWave()
{
	finishEncoding();
}




bool AudioFileWave::startEncoding()
{
	m_si.samplerate = sampleRate();
	m_si.channels = channels();
	m_si.frames = audioEngine()->framesPerPeriod();
	m_si.sections = 1;
	m_si.seekable = 0;

	m_si.format = SF_FORMAT_WAV;

	switch( getOutputSettings().getBitDepth() )
	{
	case OutputSettings::BitDepth::Depth32Bit:
		m_si.format |= SF_FORMAT_FLOAT;
		break;
	case OutputSettings::BitDepth::Depth24Bit:
		m_si.format |= SF_FORMAT_PCM_24;
		break;
	case OutputSettings::BitDepth::Depth16Bit:
	default:
		m_si.format |= SF_FORMAT_PCM_16;
		break;
	}

	// Use file handle to handle unicode file name on Windows
	m_sf = sf_open_fd( outputFileHandle(), SFM_WRITE, &m_si, false );

	if (!m_sf)
	{
		qWarning("Error: AudioFileWave::startEncoding: %s", sf_strerror(nullptr));
		return false;
	}

	// Prevent fold overs when encountering clipped data
	sf_command(m_sf, SFC_SET_CLIPPING, nullptr, SF_TRUE);

	sf_set_string ( m_sf, SF_STR_SOFTWARE, "NoeMixerr" );

	return true;
}

void AudioFileWave::writeBuffer(const SampleFrame* _ab, const f_cnt_t _frames)
{
	OutputSettings::BitDepth bitDepth = getOutputSettings().getBitDepth();

	if( bitDepth == OutputSettings::BitDepth::Depth32Bit || bitDepth == OutputSettings::BitDepth::Depth24Bit )
	{
		auto buf = new float[_frames * channels()];
		for( f_cnt_t frame = 0; frame < _frames; ++frame )
		{
			for( ch_cnt_t chnl = 0; chnl < channels(); ++chnl )
			{
				buf[frame * channels() + chnl] = _ab[frame][chnl];
			}
		}
		sf_writef_float( m_sf, buf, _frames );
		delete[] buf;
	}
	else
	{
		auto buf = new int_sample_t[_frames * channels()];
		convertToS16(_ab, _frames, buf, isBigEndian());

		sf_writef_short( m_sf, buf, _frames );
		delete[] buf;
	}
}




void AudioFileWave::finishEncoding()
{
	if( m_sf )
	{
		sf_close( m_sf );
	}
}

} // namespace noemixerr