// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LV2_FX_CONTROL_DIALOG_H
#define LV2_FX_CONTROL_DIALOG_H

#include "EffectControlDialog.h"
#include "Lv2ViewBase.h"

namespace noemixerr
{

class Lv2FxControls;

namespace gui
{

class Lv2FxControlDialog : public EffectControlDialog, public Lv2ViewBase
{
	Q_OBJECT

public:
	Lv2FxControlDialog(Lv2FxControls *controls);

private:
	Lv2FxControls *lv2Controls();
	void modelChanged() final;
	void hideEvent(QHideEvent *event) override;
};


} // namespace gui

} // namespace noemixerr

#endif
