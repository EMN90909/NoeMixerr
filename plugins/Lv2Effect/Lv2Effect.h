// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LV2_EFFECT_H
#define LV2_EFFECT_H

#include "Effect.h"
#include "Lv2FxControls.h"

namespace noemixerr
{


class Lv2Effect : public Effect
{
	Q_OBJECT

public:
	/*
		initialization
	*/
	Lv2Effect(Model* parent, const Descriptor::SubPluginFeatures::Key* _key);

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override { return &m_controls; }

	Lv2FxControls* lv2Controls() { return &m_controls; }
	const Lv2FxControls* lv2Controls() const { return &m_controls; }

private:
	Lv2FxControls m_controls;
	std::vector<SampleFrame> m_tmpOutputSmps;
};


} // namespace noemixerr

#endif
