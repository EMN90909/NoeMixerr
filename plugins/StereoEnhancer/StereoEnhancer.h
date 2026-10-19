// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef _STEREO_ENHANCER_H
#define _STEREO_ENHANCER_H

#include "Effect.h"
#include "DspEffectLibrary.h"
#include "StereoEnhancerControls.h"

namespace noemixerr
{


class StereoEnhancerEffect : public Effect
{
public:
	StereoEnhancerEffect( Model * parent,
	                      const Descriptor::SubPluginFeatures::Key * _key );
	~StereoEnhancerEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;
	void processBypassedImpl() override;

	EffectControls * controls() override
	{
		return( &m_bbControls );
	}

	void clearMyBuffer();


private:
	DspEffectLibrary::StereoEnhancer m_seFX;
	
	SampleFrame* m_delayBuffer;
	int m_currFrame;
	bool m_delayBufferCleared = true;

	StereoEnhancerControls m_bbControls;

	friend class StereoEnhancerControls;
} ;


} // namespace noemixerr

#endif
