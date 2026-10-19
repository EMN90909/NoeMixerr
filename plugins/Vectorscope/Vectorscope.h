// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef VECTORSCOPE_H
#define VECTORSCOPE_H

#include "Effect.h"
#include "LocklessRingBuffer.h"
#include "VecControls.h"

namespace noemixerr
{


//! Top level class; handles NoeMixerr interface and accumulates data for processing.
class Vectorscope : public Effect
{
public:
	Vectorscope(Model *parent, const Descriptor::SubPluginFeatures::Key *key);
	~Vectorscope() override = default;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls *controls() override {return &m_controls;}
	LocklessRingBuffer<SampleFrame> *getBuffer() {return &m_inputBuffer;}

private:
	VecControls m_controls;

	// Maximum NoeMixerr buffer size (hard coded, the actual constant is hard to get)
	const unsigned int m_maxBufferSize = 4096;
	LocklessRingBuffer<SampleFrame> m_inputBuffer;
};


} // namespace noemixerr

#endif // VECTORSCOPE_H

