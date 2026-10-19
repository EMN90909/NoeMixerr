// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef PEAK_CONTROLLER_EFFECT_H
#define PEAK_CONTROLLER_EFFECT_H

#include "Effect.h"
#include "PeakControllerEffectControls.h"

namespace noemixerr
{


class PeakController;

class PeakControllerEffect : public Effect
{
public:
	PeakControllerEffect( Model * parent, 
						const Descriptor::SubPluginFeatures::Key * _key );
	~PeakControllerEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls * controls() override
	{
		return &m_peakControls;
	}

	float lastSample()
	{
		return m_lastSample;
	}

	PeakController * controller()
	{
		return m_autoController;
	}
	
	FloatModel * attackModel()
	{
		return &( m_peakControls.m_attackModel );
	}

	FloatModel * decayModel()
	{
		return &( m_peakControls.m_decayModel );
	}

	int m_effectId;

private:
	PeakControllerEffectControls m_peakControls;

	float m_lastSample;

	PeakController * m_autoController;

	friend class PeakControllerEffectControls;

} ;


} // namespace noemixerr

#endif
