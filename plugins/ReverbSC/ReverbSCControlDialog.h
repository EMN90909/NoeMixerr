// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 Paul Batchelor
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef REVERBSC_CONTROL_DIALOG_H
#define REVERBSC_CONTROL_DIALOG_H

#include "EffectControlDialog.h"


namespace noemixerr
{

class ReverbSCControls;


namespace gui
{

class ReverbSCControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	ReverbSCControlDialog( ReverbSCControls* controls );
	~ReverbSCControlDialog() override = default;

} ;


} // namespace gui

} // namespace noemixerr

#endif
