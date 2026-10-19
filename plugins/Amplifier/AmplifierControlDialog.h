// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_AMPLIFIER_CONTROL_DIALOG_H
#define NoeMixerr_GUI_AMPLIFIER_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{

class AmplifierControls;

namespace gui
{

class AmplifierControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	AmplifierControlDialog(AmplifierControls* controls);
	~AmplifierControlDialog() override = default;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_AMPLIFIER_CONTROL_DIALOG_H
