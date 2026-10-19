// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 Paul Batchelor
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "ReverbSCControlDialog.h"

#include "embed.h"
#include "Knob.h"
#include "ReverbSCControls.h"

#include <QHBoxLayout>

namespace noemixerr::gui
{


ReverbSCControlDialog::ReverbSCControlDialog( ReverbSCControls* controls ) :
	EffectControlDialog( controls )
{
	setAutoFillBackground( true );
	QPalette pal;
	pal.setBrush( backgroundRole(), PLUGIN_NAME::getIconPixmap( "artwork" ) );
	setPalette( pal );

	auto knobLayout = new QHBoxLayout(this);
	knobLayout->setSizeConstraint(QLayout::SetFixedSize);

	auto inputGainKnob = new Knob(KnobType::Bright26, tr("Input"), this);
	inputGainKnob->setModel( &controls->m_inputGainModel );
	inputGainKnob->setHintText( tr( "Input gain:" ) , "dB" );

	auto sizeKnob = new Knob(KnobType::Bright26, tr("Size"), this);
	sizeKnob->setModel( &controls->m_sizeModel );
	sizeKnob->setHintText( tr( "Size:" ) , "" );

	auto colorKnob = new Knob(KnobType::Bright26, tr("Color"), this);
	colorKnob->setModel( &controls->m_colorModel );
	colorKnob->setHintText( tr( "Color:" ) , "" );

	auto outputGainKnob = new Knob(KnobType::Bright26, tr("Output"), this);
	outputGainKnob->setModel( &controls->m_outputGainModel );
	outputGainKnob->setHintText( tr( "Output gain:" ) , "dB" );

	knobLayout->addWidget(inputGainKnob);
	knobLayout->addWidget(sizeKnob);
	knobLayout->addWidget(colorKnob);
	knobLayout->addWidget(outputGainKnob);
}


} // namespace noemixerr::gui
