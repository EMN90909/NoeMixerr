// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef DELAYEFFECT_H
#define DELAYEFFECT_H

#include "Effect.h"
#include "DelayControls.h"

namespace noemixerr
{

class Lfo;
class StereoDelay;

class DelayEffect : public Effect
{
public:
	DelayEffect(Model* parent , const Descriptor::SubPluginFeatures::Key* key );
	~DelayEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_delayControls;
	}
	void changeSampleRate();

private:
	DelayControls m_delayControls;
	StereoDelay* m_delay;
	Lfo* m_lfo;
	float m_outGain;
	float m_currentLength;
};


} // namespace noemixerr

#endif // DELAYEFFECT_H
