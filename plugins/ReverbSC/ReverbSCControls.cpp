// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 Paul Batchelor
// See LICENSE.txt and doc/AUTHORS for original authors and license.




#include "ReverbSCControls.h"
#include "ReverbSC.h"
#include "Engine.h"

namespace noemixerr
{


ReverbSCControls::ReverbSCControls( ReverbSCEffect* effect ) :
	EffectControls( effect ),
	m_effect( effect ),
	m_inputGainModel( 0.0f, -60.0f, 15, 0.1f, this, tr( "Input gain" ) ),
	m_sizeModel( 0.89f, 0.0f, 1.0f, 0.01f, this, tr( "Size" ) ),
	m_colorModel( 10000.0f, 100.0f, 15000.0f, 0.1f, this, tr( "Color" ) ),
	m_outputGainModel( 0.0f, -60.0f, 15, 0.1f, this, tr( "Output gain" ) )
{
	connect( Engine::audioEngine(), SIGNAL( sampleRateChanged() ), this, SLOT( changeSampleRate() ));
}

void ReverbSCControls::changeControl()
{
}

void ReverbSCControls::loadSettings( const QDomElement& _this )
{
	m_inputGainModel.loadSettings( _this, "input_gain" );
	m_sizeModel.loadSettings( _this, "size" );
	m_colorModel.loadSettings( _this, "color" );
	m_outputGainModel.loadSettings( _this, "output_gain" );
}

void ReverbSCControls::saveSettings( QDomDocument& doc, QDomElement& _this )
{
	m_inputGainModel.saveSettings( doc, _this, "input_gain" ); 
	m_sizeModel.saveSettings( doc, _this, "size" ); 
	m_colorModel.saveSettings( doc, _this, "color" );
	m_outputGainModel.saveSettings( doc, _this, "output_gain" ); 
}

void ReverbSCControls::changeSampleRate()
{
	m_effect->changeSampleRate();
}


} // namespace noemixerr
