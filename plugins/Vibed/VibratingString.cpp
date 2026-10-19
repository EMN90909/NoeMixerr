// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/yahoo/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "VibratingString.h"
#include "interpolation.h"
#include "AudioEngine.h"
#include "Engine.h"
#include "NoeMixerrTypes.h"

#include <algorithm>

namespace noemixerr
{


VibratingString::VibratingString(float pitch, float pick, float pickup, const float* impulse, int len,
	sample_rate_t sampleRate, int oversample, float randomize, float stringLoss, float detune, bool state) :
	m_oversample{2 * oversample / static_cast<int>(sampleRate / Engine::audioEngine()->baseSampleRate())},
	m_randomize{randomize},
	m_stringLoss{1.0f - stringLoss},
	m_choice(fastRand(m_oversample)),
	m_state{0.1f},
	m_outsamp{std::make_unique<sample_t[]>(m_oversample)}
{
	int stringLength = static_cast<int>(m_oversample * sampleRate / pitch) + 1;
	stringLength += static_cast<int>(stringLength * -detune);

	const int pickInt = static_cast<int>(std::ceil(stringLength * pick));

	if (!state)
	{
		m_impulse = std::make_unique<float[]>(stringLength);
		resample(impulse, len, stringLength);
	}
	else
	{
		m_impulse = std::make_unique<float[]>(len);
		std::copy_n(impulse, len, m_impulse.get());
	}

	m_toBridge = VibratingString::initDelayLine(stringLength);
	m_fromBridge = VibratingString::initDelayLine(stringLength);

	VibratingString::setDelayLine(m_toBridge.get(), pickInt, m_impulse.get(), len, 0.5f, state);
	VibratingString::setDelayLine(m_fromBridge.get(), pickInt, m_impulse.get(), len, 0.5f, state);

	m_pickupLoc = static_cast<int>(pickup * stringLength);
}

std::unique_ptr<VibratingString::DelayLine> VibratingString::initDelayLine(int len)
{
	auto dl = std::make_unique<VibratingString::DelayLine>();
	dl->length = len;
	if (len > 0)
	{
		dl->data = std::make_unique<sample_t[]>(len);
		for (int i = 0; i < dl->length; ++i)
		{
			dl->data[i] = fastRandInc(m_randomize / 2.0f - m_randomize);
		}
	}
	else
	{
		dl->data = nullptr;
	}

	dl->pointer = dl->data.get();
	dl->end = dl->data.get() + len - 1;

	return dl;
}

void VibratingString::resample(const float* src, f_cnt_t srcFrames, f_cnt_t dstFrames)
{
	for (f_cnt_t frame = 0; frame < dstFrames; ++frame)
	{
		const float srcFrameFloat = frame * static_cast<float>(srcFrames) / dstFrames;
		const float fracPos = srcFrameFloat - static_cast<f_cnt_t>(srcFrameFloat);
		const f_cnt_t srcFrame = std::clamp(static_cast<f_cnt_t>(srcFrameFloat), f_cnt_t{1}, srcFrames - 3);
		m_impulse[frame] = cubicInterpolate(
			src[srcFrame - 1],
			src[srcFrame + 0],
			src[srcFrame + 1],
			src[srcFrame + 2],
			fracPos);
	}
}


} // namespace noemixerr
