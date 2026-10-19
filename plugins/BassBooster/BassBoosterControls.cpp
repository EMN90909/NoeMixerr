// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.




#include "BassBoosterControls.h"
#include "BassBooster.h"

namespace noemixerr
{


BassBoosterControls::BassBoosterControls( BassBoosterEffect* effect ) :
	EffectControls( effect ),
	m_effect( effect ),
	m_freqModel( 100.0f, 50.0f, 200.0f, 1.0f, this, tr( "Frequency" ) ),
	m_gainModel( 1.0f, 0.1f, 5.0f, 0.05f, this, tr( "Gain" ) ),
	m_ratioModel( 2.0f, 0.1f, 10.0f, 0.1f, this, tr( "Ratio" ) )
{
	connect( Engine::audioEngine(), SIGNAL( sampleRateChanged() ), this, SLOT( changeFrequency() ) );
}


void BassBoosterControls::changeFrequency()
{
	m_effect->m_frequencyChangeNeeded = true;
}



void BassBoosterControls::loadSettings( const QDomElement& _this )
{
	m_freqModel.loadSettings( _this, "freq" );
	m_gainModel.loadSettings( _this, "gain" );
	m_ratioModel.loadSettings( _this, "ratio");
}




void BassBoosterControls::saveSettings( QDomDocument& doc, QDomElement& _this )
{
	m_freqModel.saveSettings( doc, _this, "freq" );
	m_gainModel.saveSettings( doc, _this, "gain" );
	m_ratioModel.saveSettings( doc, _this, "ratio");
}


} // namespace noemixerr
