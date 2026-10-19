// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef BITCRUSH_H
#define BITCRUSH_H

#include "Effect.h"
#include "BitcrushControls.h"
#include "BasicFilters.h"


namespace noemixerr
{


class BitcrushEffect : public Effect
{
public:
	BitcrushEffect( Model* parent, const Descriptor::SubPluginFeatures::Key* key );
	~BitcrushEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_controls;
	}

private:
	void sampleRateChanged();
	float depthCrush( float in );
	float noise( float amt );

	BitcrushControls m_controls;
	
	SampleFrame* m_buffer;
	float m_sampleRate;
	StereoLinkwitzRiley m_filter;
	
	float m_bitCounterL;
	float m_rateCoeffL;
	float m_bitCounterR;
	float m_rateCoeffR;
	bool m_rateEnabled;
	
	float m_left;
	float m_right;

	int m_levels;
	float m_levelsRatio;
	bool m_depthEnabled;
	
	float m_inGain;
	float m_outGain;
	float m_outClip;

	bool m_needsUpdate;
	
	int m_silenceCounter;

	friend class BitcrushControls;
};


} // namespace noemixerr

#endif
