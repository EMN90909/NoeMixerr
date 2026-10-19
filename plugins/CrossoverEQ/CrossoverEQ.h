// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef CROSSOVEREQ_H
#define CROSSOVEREQ_H

#include "Effect.h"
#include "CrossoverEQControls.h"
#include "BasicFilters.h"

namespace noemixerr
{


class CrossoverEQEffect : public Effect
{
public:
	CrossoverEQEffect( Model* parent, const Descriptor::SubPluginFeatures::Key* key );
	~CrossoverEQEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_controls;
	}

	void clearFilterHistories();
	
private:
	CrossoverEQControls m_controls;

	void sampleRateChanged();

	float m_sampleRate;
	
	float m_gain1;
	float m_gain2;
	float m_gain3;
	float m_gain4;
	
	StereoLinkwitzRiley m_lp1;
	StereoLinkwitzRiley m_lp2;
	StereoLinkwitzRiley m_lp3;
	
	StereoLinkwitzRiley m_hp2;
	StereoLinkwitzRiley m_hp3;
	StereoLinkwitzRiley m_hp4;
	
	SampleFrame* m_tmp1;
	SampleFrame* m_tmp2;
	SampleFrame* m_work;
	
	bool m_needsUpdate;
	
	friend class CrossoverEQControls;
};


} // namespace noemixerr

#endif
