// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 Tres Finocchiaro <tres.finocchiaro/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "GbApuWrapper.h"

namespace noemixerr
{


// Sets specified sample rate and clock rate in Stereo_Buffer
blargg_err_t GbApuWrapper::setSampleRate(long sampleRate, long clockRate)
{
	Gb_Apu::output(m_buf.center(), m_buf.left(), m_buf.right());
	m_buf.clock_rate(clockRate);
	return m_buf.set_sample_rate(sampleRate);
}

// Wrap Stereo_Buffer::samples_avail()
long GbApuWrapper::samplesAvail() const
{
	return m_buf.samples_avail();
}

// Wrap Stereo_Buffer::read_samples(...)
long GbApuWrapper::readSamples(blip_sample_t* out, long count)
{
	return m_buf.read_samples(out, count);
}

// Wrap Stereo_Buffer::bass_freq(...)
void GbApuWrapper::bassFreq(int freq)
{
	m_buf.bass_freq(freq);
}

void GbApuWrapper::endFrame(blip_time_t endTime)
{
	m_time = 0;
	Gb_Apu::end_frame(endTime);
	m_buf.end_frame(endTime);
}


} // namespace noemixerr
