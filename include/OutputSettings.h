// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2017 Michael Gregorius <michael.gregorius.git/at/arcor[dot]de>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_OUTPUT_SETTINGS_H
#define NoeMixerr_OUTPUT_SETTINGS_H

#include "NoeMixerrTypes.h"

namespace noemixerr
{


class OutputSettings
{
public:
	enum class BitDepth
	{
		Depth16Bit,
		Depth24Bit,
		Depth32Bit,
		Count
	};

	enum class StereoMode
	{
		Mono,
		Stereo,
		JointStereo,
		Count
	};

public:
	OutputSettings(sample_rate_t sampleRate, bitrate_t bitRate, BitDepth bitDepth, StereoMode stereoMode)
		: m_sampleRate(sampleRate)
		, m_bitRate(bitRate)
		, m_bitDepth(bitDepth)
		, m_stereoMode(stereoMode)
		, m_compressionLevel(0.625) // 5/8
	{
	}

	OutputSettings(sample_rate_t sampleRate, bitrate_t bitRate, BitDepth bitDepth)
		: OutputSettings(sampleRate, bitRate, bitDepth, StereoMode::Stereo)
	{
	}

	sample_rate_t getSampleRate() const { return m_sampleRate; }
	void setSampleRate(sample_rate_t sampleRate) { m_sampleRate = sampleRate; }

	bitrate_t bitrate() const { return m_bitRate; }
	void setBitrate(bitrate_t bitrate) { m_bitRate = bitrate; }

	BitDepth getBitDepth() const { return m_bitDepth; }
	void setBitDepth(BitDepth bitDepth) { m_bitDepth = bitDepth; }

	StereoMode getStereoMode() const { return m_stereoMode; }
	void setStereoMode(StereoMode stereoMode) { m_stereoMode = stereoMode; }


	double getCompressionLevel() const{ return m_compressionLevel; }
	void setCompressionLevel(double level){
		// legal range is 0.0 to 1.0.
		m_compressionLevel = level;
	}

private:
	sample_rate_t m_sampleRate;
	bitrate_t m_bitRate;
	BitDepth m_bitDepth;
	StereoMode m_stereoMode;
	double m_compressionLevel;
};


} // namespace noemixerr

#endif // NoeMixerr_OUTPUT_SETTINGS_H
