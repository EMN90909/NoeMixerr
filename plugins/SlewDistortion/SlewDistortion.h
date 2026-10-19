// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_SLEW_DISTORTION_H
#define NoeMixerr_SLEW_DISTORTION_H

#include "Effect.h"
#include "SlewDistortionControls.h"

#include "BasicFilters.h"
#include "noemixerr_math.h"
#include "OversamplingHelpers.h"

namespace noemixerr
{
constexpr inline float SLEW_DISTORTION_MIN_FLOOR = 0.0012589f;// -72 dBFS
constexpr inline float SLEW_DISTORTION_DC_FREQ = 7.f;

class SlewDistortion : public Effect
{
	Q_OBJECT
public:
	SlewDistortion(Model* parent, const Descriptor::SubPluginFeatures::Key* key);
	~SlewDistortion() override = default;
	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_slewdistortionControls;
	}
	
	float msToCoeff(float ms)
	{
		return (ms == 0) ? 0 : std::exp(m_coeffPrecalc / ms);
	}
private slots:
	void changeSampleRate();
private:
	alignas(16) std::array<float, 4> m_inPeakDisplay = {0};
	alignas(16) std::array<float, 4> m_slewOut = {0};
	alignas(16) std::array<float, 4> m_dcOffset = {0};
	alignas(16) std::array<float, 4> m_inEnv = {0};
	alignas(16) std::array<float, 4> m_outEnv = {0};
	alignas(16) std::array<float, 4> m_outPeakDisplay = {0};
	alignas(16) std::array<std::array<float, 1 << SLEWDIST_MAX_OVERSAMPLE_STAGES>, 2> m_overOuts = {};
	
	float m_sampleRate = 44100.f;
	
	int m_oldOversampleVal = -1;
	float m_coeffPrecalc = 0;
	float m_dcCoeff = 0;
	float m_biasInterpCoef = 0;
	float m_trueBias1 = 0;
	float m_trueBias2 = 0;
	
	std::array<Upsampler<SLEWDIST_MAX_OVERSAMPLE_STAGES>, 2> m_upsampler;
	std::array<Downsampler<SLEWDIST_MAX_OVERSAMPLE_STAGES>, 2> m_downsampler;
	
	StereoLinkwitzRiley m_lp;
	StereoLinkwitzRiley m_hp;
	
	SlewDistortionControls m_slewdistortionControls;
	
	friend class SlewDistortionControls;
	friend class gui::SlewDistortionControlDialog;
};

} // namespace noemixerr

#endif // NoeMixerr_SLEW_DISTORTION_H
