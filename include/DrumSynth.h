// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 1998-2000 Paul Kellett (mda-vst.com)
// Copyright (c) 2007 Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_DRUM_SYNTH_H
#define NoeMixerr_DRUM_SYNTH_H

#include <cstddef>
#include <cstdint>

#include "NoeMixerrTypes.h"

class QString;

namespace noemixerr {

class DrumSynth
{
public:
	DrumSynth() = default;
	int GetDSFileSamples(QString dsfile, int16_t*& wave, int channels, sample_rate_t Fs);

private:
	float LoudestEnv();
	int LongestEnv();
	void UpdateEnv(int e, long t);
	void GetEnv(int env, const char* sec, const char* key, QString ini);

	float waveform(float ph, int form);

	std::size_t GetPrivateProfileString(const char* sec,
		const char* key, const char* def, char* buffer,
		std::size_t size, QString file);
	int GetPrivateProfileInt(const char* sec, const char* key, int def, QString file);
	float GetPrivateProfileFloat(const char* sec, const char* key, float def, QString file);
};

} // namespace noemixerr

#endif // NoeMixerr_DRUM_SYNTH_H
