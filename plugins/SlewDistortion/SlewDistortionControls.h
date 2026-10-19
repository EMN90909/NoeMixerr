// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_SLEW_DISTORTION_CONTROLS_H
#define NoeMixerr_SLEW_DISTORTION_CONTROLS_H

#include "EffectControls.h"
#include "SlewDistortionControlDialog.h"
#include "ComboBox.h"

namespace noemixerr
{

constexpr int SLEWDIST_MAX_OVERSAMPLE_STAGES = 5;

class SlewDistortion;

namespace gui
{
class SlewDistortionControlDialog;
}

enum class SlewDistortionType : int
{
	HardClip = 0,
	Tanh,
	FastSoftClip1,
	FastSoftClip2,
	Sinusoidal,
	Foldback,
	FullRectify,
	HalfRectify,
	SmoothRectify,
	Bitcrush,
	Count
};

class SlewDistortionControls : public EffectControls
{
	Q_OBJECT
public:
	SlewDistortionControls(SlewDistortion* effect);
	~SlewDistortionControls() override = default;

	void saveSettings(QDomDocument& doc, QDomElement& parent) override;
	void loadSettings(const QDomElement& parent) override;
	inline QString nodeName() const override
	{
		return "SlewDistortionControls";
	}
	gui::EffectControlDialog* createView() override
	{
		return new gui::SlewDistortionControlDialog(this);
	}
	int controlCount() override { return 32; }

private:
	SlewDistortion* m_effect;
	
	ComboBoxModel m_distType1Model;
	ComboBoxModel m_distType2Model;
	FloatModel m_drive1Model;
	FloatModel m_drive2Model;
	FloatModel m_slewUp1Model;
	FloatModel m_slewUp2Model;
	FloatModel m_slewDown1Model;
	FloatModel m_slewDown2Model;
	FloatModel m_bias1Model;
	FloatModel m_bias2Model;
	FloatModel m_warp1Model;
	FloatModel m_warp2Model;
	FloatModel m_crush1Model;
	FloatModel m_crush2Model;
	FloatModel m_outVol1Model;
	FloatModel m_outVol2Model;
	FloatModel m_attack1Model;
	FloatModel m_attack2Model;
	FloatModel m_release1Model;
	FloatModel m_release2Model;
	FloatModel m_dynamics1Model;
	FloatModel m_dynamics2Model;
	FloatModel m_dynamicSlew1Model;
	FloatModel m_dynamicSlew2Model;
	BoolModel m_dcRemoveModel;
	BoolModel m_multibandModel;
	IntModel m_oversamplingModel;
	FloatModel m_splitModel;
	FloatModel m_mix1Model;
	FloatModel m_mix2Model;
	BoolModel m_slewLink1Model;
	BoolModel m_slewLink2Model;

	friend class gui::SlewDistortionControlDialog;
	friend class SlewDistortion;
};

} // namespace noemixerr

#endif // NoeMixerr_SLEW_DISTORTION_CONTROLS_H
