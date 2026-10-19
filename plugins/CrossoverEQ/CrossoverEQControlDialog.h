// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef CROSSOVEREQ_CONTROL_DIALOG_H
#define CROSSOVEREQ_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{


class CrossoverEQControls;


namespace gui
{

class CrossoverEQControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	CrossoverEQControlDialog( CrossoverEQControls * controls );
	~CrossoverEQControlDialog() override = default;
};


} // namespace gui

} // namespace noemixerr

#endif
