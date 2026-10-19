// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.





#include <QHBoxLayout>
#include <QVBoxLayout>

#include "PeakControllerEffectControlDialog.h"
#include "PeakControllerEffectControls.h"
#include "Knob.h"
#include "LedCheckBox.h"
#include "embed.h"

namespace noemixerr::gui
{

PeakControllerEffectControlDialog::PeakControllerEffectControlDialog(
				PeakControllerEffectControls * _controls ) :
	EffectControlDialog( _controls )
{
	setWindowIcon( embed::getIconPixmap( "controller" ) );
	setAutoFillBackground( true );
	QPalette pal;
	pal.setBrush( backgroundRole(), PLUGIN_NAME::getIconPixmap( "artwork" ) );
	setPalette( pal );

	m_baseKnob = new Knob(KnobType::Bright26, tr("BASE"), this);
	m_baseKnob->setModel( &_controls->m_baseModel );
	m_baseKnob->setHintText( tr( "Base:" ) , "" );

	m_amountKnob = new Knob(KnobType::Bright26, tr("AMNT"), this);
	m_amountKnob->setModel( &_controls->m_amountModel );
	m_amountKnob->setHintText( tr( "Modulation amount:" ) , "" );

	m_amountMultKnob = new Knob(KnobType::Bright26, tr("MULT"), this);
	m_amountMultKnob->setModel( &_controls->m_amountMultModel );
	m_amountMultKnob->setHintText( tr( "Amount multiplicator:" ) , "" );

	m_attackKnob = new Knob(KnobType::Bright26, tr("ATCK"), this);
	m_attackKnob->setModel( &_controls->m_attackModel );
	m_attackKnob->setHintText( tr( "Attack:" ) , "" );

	m_decayKnob = new Knob(KnobType::Bright26, tr("DCAY"), this);
	m_decayKnob->setModel( &_controls->m_decayModel );
	m_decayKnob->setHintText( tr( "Release:" ) , "" );
	
	m_tresholdKnob = new Knob(KnobType::Bright26, tr("TRSH"), this);
	m_tresholdKnob->setModel( &_controls->m_tresholdModel );
	m_tresholdKnob->setHintText( tr( "Treshold:" ) , "" );

	m_muteLed = new LedCheckBox( tr( "Mute output" ), this );
	m_muteLed->setModel( &_controls->m_muteModel );

	m_absLed = new LedCheckBox( tr( "Absolute value" ), this );
	m_absLed->setModel( &_controls->m_absModel );

	auto mainLayout = new QVBoxLayout();
	auto knobLayout = new QHBoxLayout();
	auto ledLayout = new QHBoxLayout();

	knobLayout->addWidget( m_baseKnob );
	knobLayout->addWidget( m_amountKnob );
	knobLayout->addWidget( m_amountMultKnob );
	knobLayout->addWidget( m_attackKnob );
	knobLayout->addWidget( m_decayKnob );
	knobLayout->addWidget( m_tresholdKnob );

	ledLayout->addWidget( m_muteLed );
	ledLayout->addWidget( m_absLed );

	mainLayout->addLayout( knobLayout );
	mainLayout->addLayout( ledLayout );

	mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	setLayout( mainLayout );
}


} // namespace noemixerr::gui
