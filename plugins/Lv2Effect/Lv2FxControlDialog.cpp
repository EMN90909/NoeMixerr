// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Lv2FxControlDialog.h"

#include <QPushButton>

#include "Lv2FxControls.h"

namespace noemixerr::gui
{


Lv2FxControlDialog::Lv2FxControlDialog(Lv2FxControls *controls) :
	EffectControlDialog(controls),
	Lv2ViewBase(this, controls)
{
	if (m_reloadPluginButton) {
		connect(m_reloadPluginButton, &QPushButton::clicked,
				this, [this](){ lv2Controls()->reload(); });
	}
	if (m_toggleUIButton) {
		connect(m_toggleUIButton, &QPushButton::toggled,
			this, [this](){ toggleUI(); });
	}
	if (m_helpButton) {
		connect(m_helpButton, &QPushButton::toggled,
			this, [this](bool visible){ toggleHelp(visible); });
	}
	// for Effects, modelChanged only goes to the top EffectView
	// we need to call it manually
	modelChanged();
}




Lv2FxControls *Lv2FxControlDialog::lv2Controls()
{
	return static_cast<Lv2FxControls *>(m_effectControls);
}




void Lv2FxControlDialog::modelChanged()
{
	Lv2ViewBase::modelChanged(lv2Controls());
	connect(lv2Controls(), &Lv2FxControls::modelChanged,
		this, [this](){ this->modelChanged();} );
}




void Lv2FxControlDialog::hideEvent(QHideEvent *event)
{
	closeHelpWindow();
	QWidget::hideEvent(event);
}


} // namespace noemixerr::gui
