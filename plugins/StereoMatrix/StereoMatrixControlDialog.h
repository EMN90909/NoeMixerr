// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _STEREOMATRIX_CONTROL_DIALOG_H
#define _STEREOMATRIX_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{

class StereoMatrixControls;

namespace gui
{


class StereoMatrixControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	StereoMatrixControlDialog( StereoMatrixControls * _controls );
	~StereoMatrixControlDialog() override = default;

};


} // namespace gui

} // namespace noemixerr

#endif
