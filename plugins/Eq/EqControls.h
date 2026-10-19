// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef EQCONTROLS_H
#define EQCONTROLS_H

#include "EffectControls.h"
#include "EqSpectrumView.h"

namespace noemixerr
{


class EqEffect;

namespace gui
{
class EqControlsDialog;
}

class EqControls : public EffectControls
{
	Q_OBJECT
public:
	explicit EqControls( EqEffect* effect );
	~EqControls() override = default;

	void saveSettings ( QDomDocument& doc, QDomElement& parent ) override;

	void loadSettings ( const QDomElement &_this ) override;

	inline QString nodeName() const override
	{
		return "Eq";
	}

	int controlCount() override
	{
		return 42;
	}

	gui::EffectControlDialog* createView() override;

	float m_inPeakL;
	float m_inPeakR;
	float m_outPeakL;
	float m_outPeakR;

	// The following are linear peaks
	float m_lowShelfPeakL, m_lowShelfPeakR;
	float m_para1PeakL, m_para1PeakR;
	float m_para2PeakL, m_para2PeakR;
	float m_para3PeakL, m_para3PeakR;
	float m_para4PeakL, m_para4PeakR;
	float m_highShelfPeakL, m_highShelfPeakR;

	EqAnalyser m_inFftBands;
	EqAnalyser m_outFftBands;

	bool m_inProgress;
	bool visable();

private:
	EqEffect *m_effect;

	FloatModel m_inGainModel;
	FloatModel m_outGainModel;
	FloatModel m_lowShelfGainModel;
	FloatModel m_para1GainModel;
	FloatModel m_para2GainModel;
	FloatModel m_para3GainModel;
	FloatModel m_para4GainModel;
	FloatModel m_highShelfGainModel;

	FloatModel m_hpResModel;
	FloatModel m_lowShelfResModel;
	FloatModel m_para1BwModel;
	FloatModel m_para2BwModel;
	FloatModel m_para3BwModel;
	FloatModel m_para4BwModel;
	FloatModel m_highShelfResModel;
	FloatModel m_lpResModel;

	FloatModel m_hpFeqModel;
	FloatModel m_lowShelfFreqModel;
	FloatModel m_para1FreqModel;
	FloatModel m_para2FreqModel;
	FloatModel m_para3FreqModel;
	FloatModel m_para4FreqModel;
	FloatModel m_highShelfFreqModel;
	FloatModel m_lpFreqModel;

	BoolModel m_hpActiveModel;
	BoolModel m_lowShelfActiveModel;
	BoolModel m_para1ActiveModel;
	BoolModel m_para2ActiveModel;
	BoolModel m_para3ActiveModel;
	BoolModel m_para4ActiveModel;
	BoolModel m_highShelfActiveModel;
	BoolModel m_lpActiveModel;

	BoolModel m_lp12Model;
	BoolModel m_lp24Model;
	BoolModel m_lp48Model;

	BoolModel m_hp12Model;
	BoolModel m_hp24Model;
	BoolModel m_hp48Model;

	IntModel m_lpTypeModel;
	IntModel m_hpTypeModel;

	BoolModel m_analyseInModel;
	BoolModel m_analyseOutModel;

	friend class gui::EqControlsDialog;
	friend class EqEffect;
};


} // namespace noemixerr

#endif // EQCONTROLS_H
