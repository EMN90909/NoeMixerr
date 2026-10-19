// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef FLANGERCONTROLSDIALOG_H
#define FLANGERCONTROLSDIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{


class FlangerControls;

namespace gui
{


class FlangerControlsDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	FlangerControlsDialog( FlangerControls* controls );
	~FlangerControlsDialog() override = default;
};


} // namespace gui

} // namespace noemixerr

#endif // FLANGERCONTROLSDIALOG_H
