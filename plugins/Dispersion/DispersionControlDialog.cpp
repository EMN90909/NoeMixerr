// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "DispersionControlDialog.h"

#include <QHBoxLayout>

#include "AutomatableButton.h"
#include "DispersionControls.h"
#include "Knob.h"
#include "LcdSpinBox.h"


namespace noemixerr::gui
{


DispersionControlDialog::DispersionControlDialog(DispersionControls* controls) :
	EffectControlDialog(controls)
{
	setAutoFillBackground(true);
	auto layout = new QHBoxLayout(this);
	layout->setSpacing(5);
	layout->setSizeConstraint(QLayout::SetFixedSize);

	auto amountBox = new LcdSpinBox(3, this, "Amount");
	amountBox->setModel(&controls->m_amountModel);
	amountBox->setLabel(tr("AMOUNT"));
	amountBox->setToolTip(tr("Number of all-pass filters"));
	layout->addWidget(amountBox);
	
	auto freqKnob = new Knob(KnobType::Bright26, tr("FREQ"), this);
	freqKnob->setModel(&controls->m_freqModel);
	freqKnob->setHintText(tr("Frequency:") , tr("Hz"));
	layout->addWidget(freqKnob);
	
	auto resoKnob = new Knob(KnobType::Bright26, tr("RESO"), this);
	resoKnob->setModel(&controls->m_resoModel);
	resoKnob->setHintText(tr("Resonance:") , tr("octaves"));
	layout->addWidget(resoKnob);
	
	auto feedbackKnob = new Knob(KnobType::Bright26, tr("FEED"), this);
	feedbackKnob->setModel(&controls->m_feedbackModel);
	feedbackKnob->setHintText(tr("Feedback:") , "");
	layout->addWidget(feedbackKnob);
	
	auto dcButton = new AutomatableButton(this, tr("DC Offset Removal"));
	dcButton->setCheckable(true);
	dcButton->setText(tr("DC"));
	dcButton->setModel(&controls->m_dcModel);
	dcButton->setToolTip(tr("Remove DC Offset"));
	dcButton->setObjectName("btn");
	layout->addWidget(dcButton);
}


} // namespace noemixerr::gui
