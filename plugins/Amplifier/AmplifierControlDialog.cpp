// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "AmplifierControlDialog.h"
#include "AmplifierControls.h"
#include "embed.h"
#include "Knob.h"

#include <QGridLayout>


namespace noemixerr::gui
{

AmplifierControlDialog::AmplifierControlDialog(AmplifierControls* controls) :
	EffectControlDialog(controls)
{
	setAutoFillBackground(true);
	QPalette pal;
	pal.setBrush(backgroundRole(), PLUGIN_NAME::getIconPixmap("artwork"));
	setPalette(pal);

	QGridLayout* gridLayout = new QGridLayout(this);
	
	auto makeKnob = [this](const QString& label, const QString& hintText, const QString& unit, FloatModel* model, bool isVolume)
	{
		Knob* newKnob = isVolume
			? new VolumeKnob(KnobType::Bright26, label, this)
			: new Knob(KnobType::Bright26, label, this);
		newKnob->setModel(model);
		newKnob->setHintText(hintText, unit);
		return newKnob;
	};

	gridLayout->addWidget(makeKnob(tr("VOL"), tr("Volume:"), "%", &controls->m_volumeModel, true), 0, 0, Qt::AlignHCenter);
	gridLayout->addWidget(makeKnob(tr("PAN"), tr("Panning:"), "%", &controls->m_panModel, false), 0, 1, Qt::AlignHCenter);
	gridLayout->addWidget(makeKnob(tr("LEFT"), tr("Left gain:"), "%", &controls->m_leftModel, true), 1, 0, Qt::AlignHCenter);
	gridLayout->addWidget(makeKnob(tr("RIGHT"), tr("Right gain:"), "%", &controls->m_rightModel, true), 1, 1, Qt::AlignHCenter);
	gridLayout->setSizeConstraint(QLayout::SetFixedSize);
}

} // namespace noemixerr::gui
