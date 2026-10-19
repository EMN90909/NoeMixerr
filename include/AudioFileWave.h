// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_FILE_WAVE_H
#define NoeMixerr_AUDIO_FILE_WAVE_H

#include "noemixerrconfig.h"
#include "AudioFileDevice.h"

#include <sndfile.h>

namespace noemixerr
{

class AudioFileWave : public AudioFileDevice
{
public:
	AudioFileWave( OutputSettings const & outputSettings,
			const ch_cnt_t channels,
			bool & successful,
			const QString & file,
			AudioEngine* audioEngine );
	~AudioFileWave() override;

	static AudioFileDevice * getInst( const QString & outputFilename,
					  OutputSettings const & outputSettings,
					  const ch_cnt_t channels,
					  AudioEngine* audioEngine,
					  bool & successful )
	{
		return new AudioFileWave( outputSettings, channels, successful,
					  outputFilename, audioEngine );
	}


private:
	void writeBuffer(const SampleFrame* _ab, const f_cnt_t _frames) override;

	bool startEncoding();
	void finishEncoding();

private:
	SF_INFO m_si;
	SNDFILE * m_sf;
} ;


} // namespace noemixerr

#endif // NoeMixerr_AUDIO_FILE_WAVE_H
