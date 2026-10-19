// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Keratin
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_OSCILLOSCOPE_H
#define NoeMixerr_OSCILLOSCOPE_H

#include "Effect.h"
#include "OscilloscopeControls.h"
#include "LocklessRingBuffer.h"

namespace noemixerr
{

class Oscilloscope : public Effect
{
public:
	Oscilloscope(Model* parent, const Descriptor::SubPluginFeatures::Key* key);

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override { return &m_controls; }

	//! Ring buffer size for the data being transfered from the audio thread to the gui thread
	//! This is not the history length! The actual size of the history buffer is defined in OscilloscopeGraph.h
	static constexpr int InputBufferSize = 4096 * 4;

	LocklessRingBuffer<SampleFrame>& inputBuffer() { return m_inputBuffer; }

private:
	OscilloscopeControls m_controls;

	LocklessRingBuffer<SampleFrame> m_inputBuffer;

	friend class OscilloscopeControls;
};

} // namespace noemixerr

#endif // NoeMixerr_OSCILLOSCOPE_H
