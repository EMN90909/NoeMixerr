// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef BASS_BOOSTER_H
#define BASS_BOOSTER_H

#include "Effect.h"
#include "DspEffectLibrary.h"
#include "BassBoosterControls.h"

namespace noemixerr
{

class BassBoosterEffect : public Effect
{
public:
	BassBoosterEffect( Model* parent, const Descriptor::SubPluginFeatures::Key* key );
	~BassBoosterEffect() override = default;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_bbControls;
	}


protected:
	void changeFrequency();
	void changeGain();
	void changeRatio();

	bool m_frequencyChangeNeeded;

private:
	DspEffectLibrary::MonoToStereoAdaptor<DspEffectLibrary::FastBassBoost> m_bbFX;

	BassBoosterControls m_bbControls;

	friend class BassBoosterControls;

} ;


} // namespace noemixerr

#endif
