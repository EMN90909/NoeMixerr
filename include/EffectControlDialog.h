// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_EFFECT_CONTROL_DIALOG_H
#define NoeMixerr_GUI_EFFECT_CONTROL_DIALOG_H

#include <QWidget>

#include "ModelView.h"

namespace noemixerr
{

class EffectControls;

namespace gui
{

class NOEMIXERR_EXPORT EffectControlDialog : public QWidget, public ModelView
{
public:
	EffectControlDialog(EffectControls* controls);
	~EffectControlDialog() override = default;

protected:
	EffectControls* m_effectControls;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_EFFECT_CONTROL_DIALOG_H
