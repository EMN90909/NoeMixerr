// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LV2_FX_CONTROLS_H
#define LV2_FX_CONTROLS_H

#include "EffectControls.h"
#include "Lv2ControlBase.h"

namespace noemixerr
{


class Lv2Effect;

namespace gui
{
class Lv2FxControlDialog;
}


class Lv2FxControls : public EffectControls, public Lv2ControlBase
{
	Q_OBJECT
signals:
	void modelChanged();
public:
	Lv2FxControls(Lv2Effect *effect, const QString &uri);
	void reload();

	void saveSettings(QDomDocument &_doc, QDomElement &_parent) override;
	void loadSettings(const QDomElement &that) override;
	inline QString nodeName() const override
	{
		return Lv2ControlBase::nodeName();
	}

	int controlCount() override;
	gui::EffectControlDialog* createView() override;

private slots:
	void changeControl();

private:
	void onSampleRateChanged();

	friend class gui::Lv2FxControlDialog;
	friend class Lv2Effect;
};


} // namespace noemixerr

#endif
