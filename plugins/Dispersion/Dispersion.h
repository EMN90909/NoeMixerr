// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef NoeMixerr_DISPERSION_H
#define NoeMixerr_DISPERSION_H

#include "DispersionControls.h"
#include "Effect.h"


namespace noemixerr
{

constexpr inline int MAX_DISPERSION_FILTERS = 999;

class DispersionEffect : public Effect
{
public:
	DispersionEffect(Model* parent, const Descriptor::SubPluginFeatures::Key* key);
	~DispersionEffect() override = default;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_dispersionControls;
	}
	
	void runDispersionAP(const int filtNum, const float apCoeff1, const float apCoeff2, std::array<sample_t, 2> &put);

private:
	DispersionControls m_dispersionControls;
	
	float m_sampleRate;
	
	int m_amountVal;
	
	using Filter = std::array<sample_t, MAX_DISPERSION_FILTERS * 2>;
	struct FilterState {
		Filter x0{};
		Filter x1{};
		Filter y0{};
		Filter y1{};
	};
	FilterState m_state = {};
	
	std::array<float, 2> m_feedbackVal{};
	std::array<float, 2> m_integrator{};

	friend class DispersionControls;
};


} // namespace noemixerr

#endif // NoeMixerr_DISPERSION_H
