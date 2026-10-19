// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef DUALFILTER_H
#define DUALFILTER_H

#include "Effect.h"
#include "DualFilterControls.h"
#include "BasicFilters.h"

namespace noemixerr
{


class DualFilterEffect : public Effect
{
public:
	DualFilterEffect( Model* parent, const Descriptor::SubPluginFeatures::Key* key );
	~DualFilterEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_dfControls;
	}

protected:
	void onEnabledChanged() override;

private:
	DualFilterControls m_dfControls;

	BasicFilters<2> * m_filter1;
	BasicFilters<2> * m_filter2;
	
	bool m_filter1changed;
	bool m_filter2changed;

	float m_currentCut1;
	float m_currentRes1;
	float m_currentCut2;
	float m_currentRes2;

	friend class DualFilterControls;

} ;


} // namespace noemixerr

#endif
