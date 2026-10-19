// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 Paul Batchelor
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef REVERBSC_H
#define REVERBSC_H

#include "Effect.h"
#include "ReverbSCControls.h"

extern "C" {
    #include "base.h"
    #include "revsc.h"
    #include "dcblock.h"
}


namespace noemixerr
{


class ReverbSCEffect : public Effect
{
public:
	ReverbSCEffect( Model* parent, const Descriptor::SubPluginFeatures::Key* key );
	~ReverbSCEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_reverbSCControls;
	}

	void changeSampleRate();

private:
	ReverbSCControls m_reverbSCControls;
	sp_data *sp;
	sp_revsc *revsc;
	sp_dcblock *dcblk[2];
	QMutex mutex;
	friend class ReverbSCControls;
} ;


} // namespace noemixerr

#endif
