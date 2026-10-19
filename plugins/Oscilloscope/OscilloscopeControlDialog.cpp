// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025-2026 Keratin
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "OscilloscopeControlDialog.h"
#include "OscilloscopeControls.h"
#include "OscilloscopeGraph.h"
#include "embed.h"
#include "Knob.h"
#include "LedCheckBox.h"
#include "PixmapButton.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace noemixerr::gui
{

OscilloscopeControlDialog::OscilloscopeControlDialog(OscilloscopeControls* controls) :
	EffectControlDialog(controls)
{
	setAutoFillBackground(true);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(5);
	OscilloscopeGraph* graph = new OscilloscopeGraph(this, controls);
	mainLayout->addWidget(graph);

	QWidget* controlsWidget = new QWidget(this);
	mainLayout->addWidget(controlsWidget);
	QHBoxLayout* controlsLayout = new QHBoxLayout(controlsWidget);
	controlsLayout->setContentsMargins(5, 0, 5, 0);
	controlsLayout->setSpacing(10);


	PixmapButton* pauseButton = new PixmapButton(this, tr("Pause"));
	pauseButton->setToolTip(tr("Pause"));
	pauseButton->setActiveGraphic(embed::getIconPixmap("play"));
	pauseButton->setInactiveGraphic(embed::getIconPixmap("pause"));
	pauseButton->setCheckable(true);
	pauseButton->setModel(&controls->m_pauseModel);
	controlsLayout->addWidget(pauseButton);

	LedCheckBox* stereoCheck = new LedCheckBox("Stereo", this, tr("Stereo"), LedCheckBox::LedColor::Green);
	stereoCheck->setModel(&controls->m_stereoModel);
	controlsLayout->addWidget(stereoCheck);

	Knob* lengthKnob = new Knob(KnobType::Bright26, tr("Window Size"), this);
	lengthKnob->setModel(&controls->m_lengthModel);
	lengthKnob->setUnit(" ms");
	controlsLayout->addWidget(lengthKnob);

	Knob* phaseKnob = new Knob(KnobType::Bright26, tr("Offset"), this);
	phaseKnob->setModel(&controls->m_phaseModel);
	controlsLayout->addWidget(phaseKnob);

	Knob* ampknob = new VolumeKnob(KnobType::Bright26, tr("Scale"), this);
	ampknob->setModel(&controls->m_ampModel);
	controlsLayout->addWidget(ampknob);
}



} // namespace noemixerr::gui
