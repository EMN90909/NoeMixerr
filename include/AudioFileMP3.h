// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 to present Michael Gregorius <michael.gregorius.git/at/arcor[dot]de>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_FILE_MP3_H
#define NoeMixerr_AUDIO_FILE_MP3_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_MP3LAME

#include "AudioFileDevice.h"

#include "lame/lame.h"

namespace noemixerr
{

class AudioFileMP3 : public AudioFileDevice
{
public:
	AudioFileMP3( OutputSettings const & outputSettings,
			const ch_cnt_t _channels,
			bool & successful,
			const QString & _file,
			AudioEngine* audioEngine );
	~AudioFileMP3() override;

	static AudioFileDevice * getInst( const QString & outputFilename,
					  OutputSettings const & outputSettings,
					  const ch_cnt_t channels,
					  AudioEngine* audioEngine,
					  bool & successful )
	{
		return new AudioFileMP3( outputSettings, channels, successful,
					 outputFilename, audioEngine );
	}

protected:
	void writeBuffer(const SampleFrame* /* _buf*/, const f_cnt_t /*_frames*/) override;

private:
	void flushRemainingBuffers();
	bool initEncoder();
	void tearDownEncoder();

private:
	lame_t m_lame;
};

} // namespace noemixerr

#endif // NoeMixerr_HAVE_MP3LAME

#endif // NoeMixerr_AUDIO_FILE_MP3_H
