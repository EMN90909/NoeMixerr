// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 Tres Finocchiaro <tres.finocchiaro/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GB_APU_WRAPPER_H
#define NoeMixerr_GB_APU_WRAPPER_H

#include <Gb_Apu.h>
#include <Multi_Buffer.h>

namespace noemixerr
{


class GbApuWrapper : private Gb_Apu
{
public:
	GbApuWrapper() = default;
	~GbApuWrapper() = default;

	blargg_err_t setSampleRate(long sampleRate, long clockRate);
	void writeRegister(unsigned addr, int data) { Gb_Apu::write_register(fakeClock(), addr, data); }
	long samplesAvail() const;
	long readSamples(blip_sample_t* out, long count);
	void trebleEq(const blip_eq_t& eq) { Gb_Apu::treble_eq(eq); }
	void bassFreq(int freq);
	void endFrame(blip_time_t endTime);

private:
	Stereo_Buffer m_buf;

	// Fake CPU timing
	blip_time_t fakeClock() { return m_time += 4; }
	blip_time_t m_time = 0;
};


} // namespace noemixerr

#endif // NoeMixerr_GB_APU_WRAPPER_H
