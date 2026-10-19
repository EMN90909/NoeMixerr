// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef DYNPROC_CONTROL_DIALOG_H
#define DYNPROC_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{


class DynProcControls;


namespace gui
{

class DynProcControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	DynProcControlDialog( DynProcControls * _controls );
	~DynProcControlDialog() override = default;


private:

} ;


} // namespace gui

} // namespace noemixerr

#endif
