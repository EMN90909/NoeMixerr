// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef NoeMixerr_LOMM_H
#define NoeMixerr_LOMM_H

#include "LOMMControls.h"
#include "Effect.h"

#include "BasicFilters.h"

namespace noemixerr
{

constexpr inline float LOMM_MIN_FLOOR = 0.00012589f;// -72 dBFS
constexpr inline float LOMM_MAX_LOOKAHEAD = 20.f;
constexpr inline float LOMM_AUTO_TIME_ADJUST = 5.f;

class LOMMEffect : public Effect
{
	Q_OBJECT
public:
	LOMMEffect(Model* parent, const Descriptor::SubPluginFeatures::Key* key);
	~LOMMEffect() override = default;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls* controls() override
	{
		return &m_lommControls;
	}
	
	inline float msToCoeff(float ms)
	{
		return (ms == 0) ? 0 : std::exp(m_coeffPrecalc / ms);
	}

private slots:
	void changeSampleRate();

private:
	LOMMControls m_lommControls;
	
	float m_sampleRate;
	
	StereoLinkwitzRiley m_lp1;
	StereoLinkwitzRiley m_lp2;
	
	StereoLinkwitzRiley m_hp1;
	StereoLinkwitzRiley m_hp2;
	
	BasicFilters<2> m_ap;
	
	bool m_needsUpdate;
	float m_coeffPrecalc;
	
	std::array<std::array<float, 2>, 3> m_yL;
	std::array<std::array<float, 2>, 3> m_rms;
	std::array<std::array<float, 2>, 3> m_gainResult;
	
	std::array<std::array<float, 2>, 3> m_displayIn;
	std::array<std::array<float, 2>, 3> m_displayOut;
	
	std::array<float, 2> m_crestPeakVal;
	std::array<float, 2> m_crestRmsVal;
	std::array<float, 2> m_crestFactorVal;
	float m_crestTimeConst = 0.0f;
	
	std::array<std::array<float, 2>, 3> m_prevOut;
	
	std::array<std::array<std::vector<float>, 2>, 3> m_inLookBuf;
	std::array<std::array<std::vector<float>, 2>, 3> m_scLookBuf;
	
	int m_lookWrite = 0;
	int m_lookBufLength = 0;
	
	friend class LOMMControls;
	friend class gui::LOMMControlDialog;
};


} // namespace noemixerr

#endif // NoeMixerr_LOMM_H
