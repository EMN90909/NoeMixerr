// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "EffectControlDialog.h"

#include "EffectControls.h"

namespace noemixerr::gui
{

EffectControlDialog::EffectControlDialog(EffectControls* controls)
	: QWidget{nullptr}
	, ModelView{controls, this}
	, m_effectControls{controls}
{
	setWindowTitle(m_effectControls->effect()->displayName());
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

} // namespace noemixerr::gui
