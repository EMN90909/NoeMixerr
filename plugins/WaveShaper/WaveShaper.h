// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef _WAVESHAPER_H
#define _WAVESHAPER_H

#include "Effect.h"
#include "WaveShaperControls.h"

namespace noemixerr
{


class WaveShaperEffect : public Effect
{
public:
	WaveShaperEffect( Model * _parent,
			const Descriptor::SubPluginFeatures::Key * _key );
	~WaveShaperEffect() override = default;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls * controls() override
	{
		return( &m_wsControls );
	}


private:

	WaveShaperControls m_wsControls;

	friend class WaveShaperControls;

} ;


} // namespace noemixerr


#endif
