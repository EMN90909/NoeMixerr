// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_DISPERSION_CONTROL_DIALOG_H
#define NoeMixerr_GUI_DISPERSION_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{

class DispersionControls;


namespace gui
{

class DispersionControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	DispersionControlDialog(DispersionControls* controls);
	~DispersionControlDialog() override = default;
};


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_DISPERSION_CONTROL_DIALOG_H
