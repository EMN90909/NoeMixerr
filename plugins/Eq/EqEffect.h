// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef EQEFFECT_H
#define EQEFFECT_H

#include "Effect.h"
#include "EqControls.h"
#include "EqFilter.h"

#include <algorithm>


namespace noemixerr
{


class EqEffect : public Effect
{
public:
	EqEffect( Model * parent , const Descriptor::SubPluginFeatures::Key * key );
	~EqEffect() override = default;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls * controls() override
	{
		return &m_eqControls;
	}
	inline void gain( SampleFrame* buf, const f_cnt_t frames, float scale, SampleFrame* peak )
	{
		peak[0][0] = 0.0f; peak[0][1] = 0.0f;
		for( f_cnt_t f = 0; f < frames; ++f )
		{
			auto & sf = buf[f];

			// Apply gain to sample frame
			sf[0] *= scale;
			sf[1] *= scale;

			// Update peaks
			peak[0][0] = std::max(peak[0][0], (float)fabs(sf[0]));
			peak[0][1] = std::max(peak[0][1], (float)fabs(sf[1]));
		}
	}

private:
	EqControls m_eqControls;

	EqHp12Filter m_hp12;
	EqHp12Filter m_hp24;
	EqHp12Filter m_hp480;
	EqHp12Filter m_hp481;

	EqLowShelfFilter m_lowShelf;

	EqPeakFilter m_para1;
	EqPeakFilter m_para2;
	EqPeakFilter m_para3;
	EqPeakFilter m_para4;

	EqHighShelfFilter m_highShelf;

	EqLp12Filter m_lp12;
	EqLp12Filter m_lp24;
	EqLp12Filter m_lp480;
	EqLp12Filter m_lp481;

	float m_inGain;
	float m_outGain;

	float linearPeakBand(float minF, float maxF, EqAnalyser*, int);

	inline float bandToFreq ( int index , int sampleRate )
	{
		return index * sampleRate / ( MAX_BANDS * 2 );
	}

	void setBandPeaks( EqAnalyser * fft , int );
};


} // namespace noemixerr

#endif // EQEFFECT_H
