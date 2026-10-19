// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "StereoMatrixControlDialog.h"

#include <QHBoxLayout>
#include "embed.h"
#include "Knob.h"
#include "StereoMatrixControls.h"

namespace noemixerr::gui
{


StereoMatrixControlDialog::StereoMatrixControlDialog(StereoMatrixControls* controls) :
	EffectControlDialog(controls)
{
	QPalette pal;
	setAutoFillBackground(true);
	setFixedSize(160, 185);
	pal.setBrush(backgroundRole(), PLUGIN_NAME::getIconPixmap("artwork"));
	setPalette(pal);

	auto layout = new QHBoxLayout(this);

	const auto makeKnob = [this, layout](
		FloatModel *model,
		const QString &txt_before
	) {
		auto k = new Knob(KnobType::Bright26, this);
		k->setModel(model);
		k->setHintText(txt_before, "");
		layout->addWidget(k, 0, Qt::AlignHCenter);
		return k;
	};

	makeKnob(&controls->m_llModel, tr("Left to Left Vol:"));
	makeKnob(&controls->m_lrModel, tr("Left to Right Vol:"));
	makeKnob(&controls->m_rlModel, tr("Right to Left Vol:"));
	makeKnob(&controls->m_rrModel, tr("Right to Right Vol:"));
}


} // namespace noemixerr::gui
