// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 to present Levin Oehlmann <irrenhaus3/at/gmail[dot]com> et al.
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_FILE_FLAC_H
#define NoeMixerr_AUDIO_FILE_FLAC_H

#include "noemixerrconfig.h"

#include "AudioFileDevice.h"
#include <sndfile.h>

namespace noemixerr
{

class AudioFileFlac : public AudioFileDevice
{
public:
	AudioFileFlac(OutputSettings const& outputSettings,
			ch_cnt_t const channels,
			bool& successful,
			QString const& file,
			AudioEngine* audioEngine
	);

	~AudioFileFlac() override;

	static AudioFileDevice* getInst(QString const& outputFilename,
			OutputSettings const& outputSettings,
			ch_cnt_t const channels,
			AudioEngine* audioEngine,
			bool& successful)
	{
		return new AudioFileFlac(
			outputSettings,
			channels,
			successful,
			outputFilename,
			audioEngine
		);
	}

private:

	SF_INFO  m_sfinfo;
	SNDFILE* m_sf;

	void writeBuffer(const SampleFrame* _ab, f_cnt_t const frames) override;

	bool startEncoding();
	void finishEncoding();

};


} // namespace noemixerr

#endif // NoeMixerr_AUDIO_FILE_FLAC_H
