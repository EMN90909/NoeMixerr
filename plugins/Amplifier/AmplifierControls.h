// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AMPLIFIER_CONTROLS_H
#define NoeMixerr_AMPLIFIER_CONTROLS_H

#include "EffectControls.h"
#include "AmplifierControlDialog.h"

namespace noemixerr
{

class AmplifierEffect;

class AmplifierControls : public EffectControls
{
	Q_OBJECT
public:
	AmplifierControls(AmplifierEffect* effect);
	~AmplifierControls() override = default;

	void saveSettings(QDomDocument& doc, QDomElement& parent) override;
	void loadSettings(const QDomElement& parent) override;
	inline QString nodeName() const override
	{
		return "AmplifierControls";
	}
	gui::EffectControlDialog* createView() override
	{
		return new gui::AmplifierControlDialog(this);
	}
	int controlCount() override { return 4; }

private:
	AmplifierEffect* m_effect;
	FloatModel m_volumeModel;
	FloatModel m_panModel;
	FloatModel m_leftModel;
	FloatModel m_rightModel;

	friend class gui::AmplifierControlDialog;
	friend class AmplifierEffect;
};

} // namespace noemixerr

#endif // NoeMixerr_AMPLIFIER_CONTROLS_H
