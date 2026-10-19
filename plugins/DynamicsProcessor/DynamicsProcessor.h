// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef DYNPROC_H
#define DYNPROC_H

#include "Effect.h"
#include "DynamicsProcessorControls.h"

namespace noemixerr
{

class RmsHelper;


class DynProcEffect : public Effect
{
public:
	DynProcEffect( Model * _parent,
			const Descriptor::SubPluginFeatures::Key * _key );
	~DynProcEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;
	void processBypassedImpl() override;

	EffectControls * controls() override
	{
		return( &m_dpControls );
	}


private:
	void calcAttack();
	void calcRelease();

	DynProcControls m_dpControls;

// this member array is needed for peak detection 
	float m_currentPeak[2];
	double m_attCoeff;
	double m_relCoeff;
	
	bool m_needsUpdate;
	
	RmsHelper * m_rms [2];

	friend class DynProcControls;

} ;


} // namespace noemixerr

#endif
