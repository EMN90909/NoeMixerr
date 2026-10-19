// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "AudioFileOgg.h"

#ifdef NoeMixerr_HAVE_OGGVORBIS

#include <vorbis/vorbisenc.h>

#include "SampleFrame.h"
#include "noemixerr_constants.h"

namespace noemixerr
{

AudioFileOgg::AudioFileOgg(OutputSettings const& outputSettings, const ch_cnt_t channels, bool& successful,
	const QString& file, AudioEngine* audioEngine)
	: AudioFileDevice(outputSettings, channels, file, audioEngine)
{
	vorbis_info_init(&m_vi);

	const auto bitrate = outputSettings.bitrate();
	static constexpr auto maxBitrate = 320;

	if (vorbis_encode_init_vbr(&m_vi, channels, sampleRate(), static_cast<float>(bitrate) / maxBitrate))
	{
		successful = false;
		return;
	}

	vorbis_analysis_init(&m_vds, &m_vi);
	vorbis_comment_init(&m_vc);
	vorbis_comment_add_tag(&m_vc, "Cool", "This song has been made using NoeMixerr");

	auto headerPackets = std::array<ogg_packet, 3>{};
	vorbis_analysis_headerout(&m_vds, &m_vc, &headerPackets[0], &headerPackets[1], &headerPackets[2]);

	srand(time(nullptr));
	ogg_stream_init(&m_oss, rand());

	ogg_stream_packetin(&m_oss, &headerPackets[0]);
	ogg_stream_packetin(&m_oss, &headerPackets[1]);
	ogg_stream_packetin(&m_oss, &headerPackets[2]);

	while (ogg_stream_flush(&m_oss, &m_page))
	{
		writeData(m_page.header, m_page.header_len);
		writeData(m_page.body, m_page.body_len);
	}

	vorbis_block_init(&m_vds, &m_vb);
	successful = true;
}

AudioFileOgg::~AudioFileOgg()
{
	// writing 0 frames is how we flush any remaining data to the file
	writeBuffer(nullptr, 0);

	ogg_stream_clear(&m_oss);
	vorbis_block_clear(&m_vb);
	vorbis_dsp_clear(&m_vds);
	vorbis_comment_clear(&m_vc);
	vorbis_info_clear(&m_vi);
}

void AudioFileOgg::writeBuffer(const SampleFrame* _ab, const f_cnt_t _frames)
{
	if (_frames == 0)
	{
		vorbis_analysis_wrote(&m_vds, 0);
	}
	else
	{
		const auto vab = vorbis_analysis_buffer(&m_vds, _frames);
		for (auto c = 0; c < channels(); ++c)
		{
			if (c < DEFAULT_CHANNELS)
			{
				for (auto i = std::size_t{0}; i < _frames; ++i)
				{
					vab[c][i] = _ab[i][c];
				}
			}
			else
			{
				std::fill_n(vab[c], _frames, 0.0f);
			}
		}

		vorbis_analysis_wrote(&m_vds, _frames);
	}

	while (vorbis_analysis_blockout(&m_vds, &m_vb) == 1)
	{
		vorbis_analysis(&m_vb, nullptr);
		vorbis_bitrate_addblock(&m_vb);

		while (vorbis_bitrate_flushpacket(&m_vds, &m_packet))
		{
			ogg_stream_packetin(&m_oss, &m_packet);

			do
			{
				if (ogg_stream_pageout(&m_oss, &m_page) == 0) { break; }
				writeData(m_page.header, m_page.header_len);
				writeData(m_page.body, m_page.body_len);
			} while (!ogg_page_eos(&m_page));
		}
	}
}

} // namespace noemixerr

#endif // NoeMixerr_HAVE_OGGVORBIS


