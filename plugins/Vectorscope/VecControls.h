// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef VECCONTROLS_H
#define VECCONTROLS_H


#include "EffectControls.h"

namespace noemixerr
{


class Vectorscope;

namespace gui
{
class VecControlsDialog;
}

// Holds all the configuration values
class VecControls : public EffectControls
{
	Q_OBJECT
public:
	explicit VecControls(Vectorscope *effect);
	~VecControls() override = default;

	gui::EffectControlDialog* createView() override;

	void saveSettings (QDomDocument &document, QDomElement &element) override;
	void loadSettings (const QDomElement &element) override;

	QString nodeName() const override {return "Vectorscope";}
	int controlCount() override {return 3;}

	const BoolModel& getLogarithmicModel() const { return m_logarithmicModel; }
	const BoolModel& getLinesModel() const { return m_linesModeModel; }

private:
	Vectorscope *m_effect;

	BoolModel m_logarithmicModel;
	BoolModel m_linesModeModel;

	friend class gui::VecControlsDialog;
};


} // namespace noemixerr

#endif // VECCONTROLS_H
