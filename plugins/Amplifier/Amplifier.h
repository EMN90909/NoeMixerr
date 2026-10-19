// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AMPLIFIER_H
#define NoeMixerr_AMPLIFIER_H

#include "Effect.h"
#include "AmplifierControls.h"

namespace noemixerr
{

class AmplifierEffect : public Effect
{
public:
	AmplifierEffect(Model* parent, const Descriptor::SubPluginFeatures::Key* key);
	~AmplifierEffect() override = default;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_ampControls;
	}

private:
	AmplifierControls m_ampControls;

	friend class AmplifierControls;
};

} // namespace noemixerr

#endif // NoeMixerr_AMPLIFIER_H
