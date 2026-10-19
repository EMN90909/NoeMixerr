// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef FLANGEREFFECT_H
#define FLANGEREFFECT_H

#include "Effect.h"
#include "FlangerControls.h"

namespace noemixerr
{

class MonoDelay;
class QuadratureLfo;


class FlangerEffect : public Effect
{
public:
	FlangerEffect( Model* parent , const Descriptor::SubPluginFeatures::Key* key );
	~FlangerEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_flangerControls;
	}
	void changeSampleRate();
	void restartLFO();

private:
	FlangerControls m_flangerControls;
	MonoDelay* m_lDelay;
	MonoDelay* m_rDelay;
	QuadratureLfo* m_lfo;
};


} // namespace noemixerr

#endif // FLANGEREFFECT_H
