// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020 Lost Robot <r94231@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef COMPRESSOR_CONTROLS_H
#define COMPRESSOR_CONTROLS_H

#include "CompressorControlDialog.h"

#include "EffectControls.h"

namespace noemixerr
{

class CompressorEffect;


class CompressorControls : public EffectControls
{
	Q_OBJECT
public:
	CompressorControls(CompressorEffect* effect);

	void saveSettings(QDomDocument & _doc, QDomElement & _parent) override;
	void loadSettings(const QDomElement & _this) override;
	inline QString nodeName() const override
	{
		return "CompressorControls";
	}

	int controlCount() override
	{
		return 28;
	}

	gui::EffectControlDialog* createView() override
	{
		return new gui::CompressorControlDialog(this);
	}

private:
	CompressorEffect * m_effect;

	FloatModel m_thresholdModel;
	FloatModel m_ratioModel;
	FloatModel m_attackModel;
	FloatModel m_releaseModel;
	FloatModel m_kneeModel;
	FloatModel m_holdModel;
	FloatModel m_rangeModel;
	FloatModel m_rmsModel;
	IntModel m_midsideModel;
	IntModel m_peakmodeModel;
	FloatModel m_lookaheadLengthModel;
	FloatModel m_inBalanceModel;
	FloatModel m_outBalanceModel;
	IntModel m_limiterModel;
	FloatModel m_outGainModel;
	FloatModel m_inGainModel;
	FloatModel m_blendModel;
	FloatModel m_stereoBalanceModel;
	BoolModel m_autoMakeupModel;
	BoolModel m_auditionModel;
	BoolModel m_feedbackModel;
	FloatModel m_autoAttackModel;
	FloatModel m_autoReleaseModel;
	BoolModel m_lookaheadModel;
	FloatModel m_tiltModel;
	FloatModel m_tiltFreqModel;
	IntModel m_stereoLinkModel;
	FloatModel m_mixModel;

	float m_inPeakL;
	float m_inPeakR;
	float m_outPeakL;
	float m_outPeakR;

	friend class gui::CompressorControlDialog;
	friend class CompressorEffect;

} ;


} // namespace noemixerr

#endif
