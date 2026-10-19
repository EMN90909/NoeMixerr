// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GRANULAR_PITCH_SHIFTER_CONTROL_DIALOG_H
#define NoeMixerr_GRANULAR_PITCH_SHIFTER_CONTROL_DIALOG_H

#include "ComboBoxModel.h"
#include "EffectControls.h"
#include "GranularPitchShifterControlDialog.h"

namespace noemixerr
{

class GranularPitchShifterEffect;

class GranularPitchShifterControls : public EffectControls
{
	Q_OBJECT
public:
	GranularPitchShifterControls(GranularPitchShifterEffect* effect);
	~GranularPitchShifterControls() override = default;

	void saveSettings(QDomDocument& doc, QDomElement& parent) override;
	void loadSettings(const QDomElement& parent) override;
	inline QString nodeName() const override
	{
		return "GranularPitchShifterControls";
	}
	gui::EffectControlDialog* createView() override
	{
		return new gui::GranularPitchShifterControlDialog(this);
	}
	int controlCount() override { return 4; }
	
public slots:
	void updateRange();
	
private:
	GranularPitchShifterEffect* m_effect;
	FloatModel m_pitchModel;
	FloatModel m_sizeModel;
	FloatModel m_sprayModel;
	FloatModel m_jitterModel;
	FloatModel m_twitchModel;
	FloatModel m_pitchSpreadModel;
	FloatModel m_spraySpreadModel;
	FloatModel m_shapeModel;
	FloatModel m_fadeLengthModel;
	FloatModel m_feedbackModel;
	FloatModel m_minLatencyModel;
	BoolModel m_prefilterModel;
	FloatModel m_densityModel;
	FloatModel m_glideModel;
	ComboBoxModel m_rangeModel;

	friend class gui::GranularPitchShifterControlDialog;
	friend class GranularPitchShifterEffect;
};

} // namespace noemixerr

#endif // NoeMixerr_GRANULAR_PITCH_SHIFTER_CONTROL_DIALOG_H
