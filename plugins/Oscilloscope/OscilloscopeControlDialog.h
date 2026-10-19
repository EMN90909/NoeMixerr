// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025-2026 Keratin
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_OSCILLOSCOPE_CONTROL_DIALOG_H
#define NoeMixerr_GUI_OSCILLOSCOPE_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{

class OscilloscopeControls;
class FloatModel;

namespace gui
{

class Knob;

class OscilloscopeControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	OscilloscopeControlDialog(OscilloscopeControls* controls);
	~OscilloscopeControlDialog() override = default;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_OSCILLOSCOPE_CONTROL_DIALOG_H
