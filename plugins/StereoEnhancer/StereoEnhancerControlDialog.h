// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _STEREOENHANCER_CONTROL_DIALOG_H
#define _STEREOENHANCER_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{

class StereoEnhancerControls;


namespace gui
{


class StereoEnhancerControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	StereoEnhancerControlDialog( StereoEnhancerControls * _controls );
	~StereoEnhancerControlDialog() override = default;

};

} // namespace gui

} // namespace noemixerr

#endif
