// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _BASSBOOSTER_CONTROL_DIALOG_H
#define _BASSBOOSTER_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{

class BassBoosterControls;

namespace gui
{

class BassBoosterControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	BassBoosterControlDialog( BassBoosterControls* controls );
	~BassBoosterControlDialog() override = default;

} ;


} // namespace gui

} // namespace noemixerr

#endif
