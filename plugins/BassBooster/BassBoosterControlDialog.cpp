// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <QHBoxLayout>
#include <QVBoxLayout>

#include "BassBoosterControlDialog.h"
#include "BassBoosterControls.h"
#include "embed.h"
#include "Knob.h"


namespace noemixerr::gui
{


BassBoosterControlDialog::BassBoosterControlDialog( BassBoosterControls* controls ) :
	EffectControlDialog( controls )
{
	setAutoFillBackground( true );
	QPalette pal;
	pal.setBrush( backgroundRole(), PLUGIN_NAME::getIconPixmap( "artwork" ) );
	setPalette( pal );

	auto tl = new QVBoxLayout(this);
	tl->addSpacing( 4 );

	auto l = new QHBoxLayout;

	auto freqKnob = new Knob(KnobType::Bright26, tr("FREQ"), this);
	freqKnob->setModel( &controls->m_freqModel );
	freqKnob->setHintText( tr( "Frequency:" ) , "Hz" );

	auto gainKnob = new Knob(KnobType::Bright26, tr("GAIN"), this);
	gainKnob->setModel( &controls->m_gainModel );
	gainKnob->setHintText( tr( "Gain:" ) , "" );

	auto ratioKnob = new Knob(KnobType::Bright26, tr("RATIO"), this);
	ratioKnob->setModel( &controls->m_ratioModel );
	ratioKnob->setHintText( tr( "Ratio:" ) , "" );

	l->addWidget( freqKnob );
	l->addWidget( gainKnob );
	l->addWidget( ratioKnob );

	tl->addLayout( l );
	setLayout( tl );
	tl->setSizeConstraint(QLayout::SetFixedSize);
}


} // namespace noemixerr::gui
