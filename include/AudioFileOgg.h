// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_FILE_OGG_H
#define NoeMixerr_AUDIO_FILE_OGG_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_OGGVORBIS

#include <vorbis/codec.h>

#include "AudioFileDevice.h"

namespace noemixerr
{

class AudioFileOgg : public AudioFileDevice
{
public:
	AudioFileOgg( OutputSettings const & outputSettings,
			const ch_cnt_t _channels,
			bool & _success_ful,
			const QString & _file,
			AudioEngine* audioEngine );
	~AudioFileOgg() override;

	static AudioFileDevice * getInst( const QString & outputFilename,
					  OutputSettings const & outputSettings,
					  const ch_cnt_t channels,
					  AudioEngine* audioEngine,
					  bool & successful )
	{
		return new AudioFileOgg( outputSettings, channels, successful, outputFilename, audioEngine );
	}

private:
	void writeBuffer(const SampleFrame* _ab, const f_cnt_t _frames) override;
	vorbis_info m_vi;
	vorbis_dsp_state m_vds;
	vorbis_comment m_vc;
	vorbis_block m_vb;
	ogg_stream_state m_oss;
	ogg_packet m_packet;
	ogg_page m_page;
};

} // namespace noemixerr

#endif // NoeMixerr_HAVE_OGGVORBIS

#endif // NoeMixerr_AUDIO_FILE_OGG_H
