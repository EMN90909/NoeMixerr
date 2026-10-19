// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_DISPERSION_CONTROLS_H
#define NoeMixerr_DISPERSION_CONTROLS_H

#include "DispersionControlDialog.h"
#include "EffectControls.h"

namespace noemixerr
{

class DispersionEffect;

class DispersionControls : public EffectControls
{
	Q_OBJECT
public:
	DispersionControls(DispersionEffect* effect);
	~DispersionControls() override = default;

	void saveSettings(QDomDocument & doc, QDomElement & parent) override;
	void loadSettings(const QDomElement & parent) override;
	inline QString nodeName() const override
	{
		return "DispersionControls";
	}

	int controlCount() override
	{
		return 5;
	}

	gui::EffectControlDialog* createView() override
	{
		return new gui::DispersionControlDialog(this);
	}

private:
	DispersionEffect* m_effect;
	IntModel m_amountModel;
	FloatModel m_freqModel;
	FloatModel m_resoModel;
	FloatModel m_feedbackModel;
	BoolModel m_dcModel;

	friend class gui::DispersionControlDialog;
	friend class DispersionEffect;
};


} // namespace noemixerr

#endif // NoeMixerr_DISPERSION_CONTROLS_H
