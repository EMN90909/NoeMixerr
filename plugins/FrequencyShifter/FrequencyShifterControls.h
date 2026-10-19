// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_FREQUENCY_SHIFTER_CONTROLS_H
#define NoeMixerr_FREQUENCY_SHIFTER_CONTROLS_H

#include "EffectControls.h"
#include "FrequencyShifterControlDialog.h"

namespace noemixerr
{

class FrequencyShifterEffect;

class FrequencyShifterControls : public EffectControls
{
	Q_OBJECT
public:
	FrequencyShifterControls(FrequencyShifterEffect* e);
	~FrequencyShifterControls() override = default;

	void saveSettings(QDomDocument& doc, QDomElement& e) override;
	void loadSettings(const QDomElement& e) override;
	QString nodeName() const override
	{
		return "FrequencyShifterControls";
	}
	gui::EffectControlDialog* createView() override
	{
		return new gui::FrequencyShifterControlDialog(this);
	}
	int controlCount() override
	{
		return 20;
	}

	FrequencyShifterEffect* m_effect;
	FloatModel m_mix;
	FloatModel m_freqShift;
	FloatModel m_spreadShift;
	FloatModel m_ring;
	FloatModel m_feedback;
	FloatModel m_delayLengthLong;
	FloatModel m_delayLengthShort;
	FloatModel m_delayDamp;
	FloatModel m_delayGlide;
	FloatModel m_lfoAmount;
	FloatModel m_lfoRate;
	FloatModel m_lfoStereoPhase;
	FloatModel m_glide;
	FloatModel m_tone;

	FloatModel m_phase;

	BoolModel m_antireflect;
	IntModel m_routeMode;

	FloatModel m_harmonics;

	BoolModel m_resetShifter;
	BoolModel m_resetLfo;
};

} // namespace noemixerr

#endif // NoeMixerr_FREQUENCY_SHIFTER_CONTROLS_H
