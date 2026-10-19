// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef VECCONTROLSDIALOG_H
#define VECCONTROLSDIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{


class VecControls;

namespace gui
{


//! Top-level widget holding the configuration GUI and vector display
class VecControlsDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	explicit VecControlsDialog(VecControls *controls);
	~VecControlsDialog() override = default;

	QSize sizeHint() const override;

private:
	VecControls *m_controls;
};


} // namespace gui

} // namespace noemixerr

#endif // VECCONTROLSDIALOG_H
