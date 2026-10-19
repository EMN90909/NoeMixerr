// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "FlangerControlsDialog.h"

#include <QVBoxLayout>

#include "embed.h"
#include "FlangerControls.h"
#include "LedCheckBox.h"
#include "TempoSyncKnob.h"

namespace noemixerr::gui
{


FlangerControlsDialog::FlangerControlsDialog( FlangerControls *controls ) :
	EffectControlDialog( controls )
{
	setAutoFillBackground( true );
	QPalette pal;
	pal.setBrush( backgroundRole(), PLUGIN_NAME::getIconPixmap( "artwork" ) );
	setPalette( pal );

	auto mainLayout = new QVBoxLayout(this);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	auto knobLayout = new QHBoxLayout();
	mainLayout->addLayout(knobLayout);

	auto delayKnob = new Knob(KnobType::Bright26, tr("DELAY"), this);
	delayKnob->setModel( &controls->m_delayTimeModel );
	delayKnob->setHintText( tr( "Delay time:" ) + " ", "s" );

	auto lfoFreqKnob = new TempoSyncKnob(KnobType::Bright26, tr("RATE"), this);
	lfoFreqKnob->setModel( &controls->m_lfoFrequencyModel );
	lfoFreqKnob->setHintText( tr( "Period:" ) , " Sec" );

	auto lfoAmtKnob = new Knob(KnobType::Bright26, tr("AMNT"), this);
	lfoAmtKnob->setModel( &controls->m_lfoAmountModel );
	lfoAmtKnob->setHintText( tr( "Amount:" ) , "" );

	auto lfoPhaseKnob = new Knob(KnobType::Bright26, tr("PHASE"), this);
	lfoPhaseKnob->setModel( &controls->m_lfoPhaseModel );
	lfoPhaseKnob->setHintText( tr( "Phase:" ) , " degrees" );

	auto feedbackKnob = new VolumeKnob(KnobType::Bright26, tr("FDBK"), this);
	feedbackKnob->setZeroDbfsPoint(1.f);
	feedbackKnob->setModel( &controls->m_feedbackModel );
	feedbackKnob->setHintText( tr( "Feedback amount:" ) , "" );

	auto whiteNoiseKnob = new VolumeKnob(KnobType::Bright26, tr("NOISE"), this);
	whiteNoiseKnob->setZeroDbfsPoint(1.f);
	whiteNoiseKnob->setModel( &controls->m_whiteNoiseAmountModel );
	whiteNoiseKnob->setHintText( tr( "White noise amount:" ) , "" );

	knobLayout->addWidget(delayKnob);
	knobLayout->addWidget(lfoFreqKnob);
	knobLayout->addWidget(lfoAmtKnob);
	knobLayout->addWidget(lfoPhaseKnob);
	knobLayout->addWidget(feedbackKnob);
	knobLayout->addWidget(whiteNoiseKnob);

	auto invertCb = new LedCheckBox(tr("Invert"), this);
	invertCb->setModel(&controls->m_invertFeedbackModel);
	
	mainLayout->addWidget(invertCb, 0, Qt::AlignLeft);
}


} // namespace noemixerr::gui
