// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 
#ifndef MULTITAP_ECHO_H
#define MULTITAP_ECHO_H

#include "Effect.h"
#include "MultitapEchoControls.h"
#include "RingBuffer.h"
#include "BasicFilters.h"

namespace noemixerr
{


class MultitapEchoEffect : public Effect
{
public:
	MultitapEchoEffect( Model* parent, const Descriptor::SubPluginFeatures::Key* key );
	~MultitapEchoEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_controls;
	}

private:
	void updateFilters( int begin, int end );
	void runFilter( SampleFrame* dst, SampleFrame* src, StereoOnePole & filter, const f_cnt_t frames );

	inline void setFilterFreq( float fc, StereoOnePole & f )
	{
		const float b1 = std::exp(-2 * std::numbers::pi_v<float> * fc);
		f.setCoeffs( 1.0f - b1, b1 );
	}

	int m_stages;

	MultitapEchoControls m_controls;
	
	float m_amp [32];
	float m_lpFreq [32];

	RingBuffer m_buffer;
	StereoOnePole m_filter [32][4];
	
	float m_sampleRate;
	float m_sampleRatio;
	
	SampleFrame* m_work;

	friend class MultitapEchoControls;

};


} // namespace noemixerr

#endif
