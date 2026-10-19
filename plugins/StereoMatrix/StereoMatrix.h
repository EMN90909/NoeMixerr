// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef _STEREO_MATRIX_H
#define _STEREO_MATRIX_H

#include "Effect.h"
#include "StereoMatrixControls.h"

namespace noemixerr
{


class StereoMatrixEffect : public Effect
{
public:
	StereoMatrixEffect( Model * parent, 
	                      const Descriptor::SubPluginFeatures::Key * _key );
	~StereoMatrixEffect() override = default;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return( &m_smControls );
	}


private:
	StereoMatrixControls m_smControls;

	friend class StereoMatrixControls;
} ;


} // namespace noemixerr

#endif
