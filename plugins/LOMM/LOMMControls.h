// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LOMM_CONTROLS_H
#define NoeMixerr_LOMM_CONTROLS_H

#include "LOMMControlDialog.h"
#include "EffectControls.h"

namespace noemixerr
{
class LOMMEffect;

class LOMMControls : public EffectControls
{
	Q_OBJECT
public:
	LOMMControls(LOMMEffect* effect);
	~LOMMControls() override = default;

	void saveSettings(QDomDocument & doc, QDomElement & parent) override;
	void loadSettings(const QDomElement & parent) override;
	inline QString nodeName() const override
	{
		return "LOMMControls";
	}

	int controlCount() override
	{
		return 49;
	}

	gui::EffectControlDialog* createView() override
	{
		m_view = new gui::LOMMControlDialog(this);
		return m_view;
	}
	
	template <typename T>
	void setInitAndReset(AutomatableModel& model, T initValue)
	{
		model.setInitValue(initValue);
		model.reset();
	}
	
public slots:
	void resetAllParameters();

private:
	LOMMEffect* m_effect;
	gui::LOMMControlDialog* m_view;
	
	FloatModel m_depthModel;
	FloatModel m_timeModel;
	FloatModel m_inVolModel;
	FloatModel m_outVolModel;
	FloatModel m_upwardModel;
	FloatModel m_downwardModel;
	FloatModel m_split1Model;
	FloatModel m_split2Model;
	BoolModel m_split1EnabledModel;
	BoolModel m_split2EnabledModel;
	BoolModel m_band1EnabledModel;
	BoolModel m_band2EnabledModel;
	BoolModel m_band3EnabledModel;
	FloatModel m_inHighModel;
	FloatModel m_inMidModel;
	FloatModel m_inLowModel;
	FloatModel m_outHighModel;
	FloatModel m_outMidModel;
	FloatModel m_outLowModel;
	FloatModel m_aThreshHModel;
	FloatModel m_aThreshMModel;
	FloatModel m_aThreshLModel;
	FloatModel m_aRatioHModel;
	FloatModel m_aRatioMModel;
	FloatModel m_aRatioLModel;
	FloatModel m_bThreshHModel;
	FloatModel m_bThreshMModel;
	FloatModel m_bThreshLModel;
	FloatModel m_bRatioHModel;
	FloatModel m_bRatioMModel;
	FloatModel m_bRatioLModel;
	FloatModel m_atkHModel;
	FloatModel m_atkMModel;
	FloatModel m_atkLModel;
	FloatModel m_relHModel;
	FloatModel m_relMModel;
	FloatModel m_relLModel;
	FloatModel m_rmsTimeModel;
	FloatModel m_kneeModel;
	FloatModel m_rangeModel;
	FloatModel m_balanceModel;
	BoolModel m_depthScalingModel;
	BoolModel m_stereoLinkModel;
	FloatModel m_autoTimeModel;
	FloatModel m_mixModel;
	BoolModel m_feedbackModel;
	BoolModel m_midsideModel;
	BoolModel m_lookaheadEnableModel;
	FloatModel m_lookaheadModel;
	BoolModel m_lowSideUpwardSuppressModel;
	
	friend class gui::LOMMControlDialog;
	friend class LOMMEffect;
};

} // namespace noemixerr

#endif // NoeMixerr_LOMM_CONTROLS_H
