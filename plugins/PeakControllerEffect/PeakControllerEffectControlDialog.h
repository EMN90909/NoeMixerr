// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _PEAK_CONTROLLER_EFFECT_CONTROL_DIALOG_H
#define _PEAK_CONTROLLER_EFFECT_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{

class PeakControllerEffectControls;

namespace gui
{
class Knob;
class LedCheckBox;


class PeakControllerEffectControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	PeakControllerEffectControlDialog(
				PeakControllerEffectControls * _controls );
	~PeakControllerEffectControlDialog() override = default;


protected:
	Knob * m_baseKnob;
	Knob * m_amountKnob;
	Knob * m_attackKnob;
	Knob * m_decayKnob;
	Knob * m_tresholdKnob;
	LedCheckBox * m_muteLed;

	LedCheckBox * m_absLed;
	Knob * m_amountMultKnob;

} ;

} // namespace gui

} // namespace noemixerr

#endif
