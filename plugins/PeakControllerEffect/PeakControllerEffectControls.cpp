// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// Copyright (c) 2009-2011 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <QDomElement>

#include "PeakControllerEffectControls.h"
#include "PeakControllerEffect.h"
#include "Song.h"
#include "noemixerr_math.h"

namespace noemixerr
{


PeakControllerEffectControls::
PeakControllerEffectControls( PeakControllerEffect * _eff ) :
	EffectControls( _eff ),
	m_effect( _eff ),
	m_baseModel(0.5f, 0.f, 1.f, 0.001f, this, tr("Base value")),
	m_amountModel(1.f, -1.f, 1.f, 0.005f, this, tr("Modulation amount")),
	m_attackModel(0, 0, 0.999f, 0.001f, this, tr("Attack")),
	m_decayModel(0, 0, 0.999f, 0.001f, this, tr("Release")),
	m_tresholdModel(0, 0, 1.f, 0.001f, this, tr("Treshold")),
	m_muteModel( false, this, tr( "Mute output" ) ),
	m_absModel( true, this, tr("Absolute value") ),
	m_amountMultModel(1.f, 0, 32, 0.2f, this, tr("Amount multiplicator"))
{
}




void PeakControllerEffectControls::loadSettings( const QDomElement & _this )
{
	m_baseModel.loadSettings( _this, "base" );
	m_effect->m_lastSample = m_baseModel.value(); //Set initial Peak Controller output to Base
	m_amountModel.loadSettings( _this, "amount" );
	m_muteModel.loadSettings( _this, "mute" );

	m_attackModel.loadSettings( _this, "attack" );
	m_decayModel.loadSettings( _this, "decay" );

	m_absModel.loadSettings( _this, "abs" );
	m_amountMultModel.loadSettings( _this, "amountmult" );
	
	m_tresholdModel.loadSettings( _this, "treshold" );

	/*If the peak controller effect is NOT loaded from project,
	 * m_effectId stored is useless.
	 * Reason to assign a random number to it:
	 * If the user clone the instrument, and m_effectId is cloned, and
	 * m_effectId is copied, then there would be two instruments
	 * having the same id.
	 */
	if( Engine::getSong()->isLoadingProject() == true )
	{
		m_effect->m_effectId = _this.attribute( "effectId" ).toInt();
	}
	else
	{
		// TODO: Fix possible collision
		m_effect->m_effectId = fastRand();
	}
}




void PeakControllerEffectControls::saveSettings( QDomDocument & _doc, 
							QDomElement & _this )
{
	_this.setAttribute( "effectId", m_effect->m_effectId );

	m_baseModel.saveSettings( _doc, _this, "base" );
	m_amountModel.saveSettings( _doc, _this, "amount" );
	m_muteModel.saveSettings( _doc, _this, "mute" );

	m_attackModel.saveSettings( _doc, _this, "attack" );
	m_decayModel.saveSettings( _doc, _this, "decay" );

	m_absModel.saveSettings( _doc,  _this, "abs" );
	m_amountMultModel.saveSettings( _doc, _this, "amountmult" );
	
	m_tresholdModel.saveSettings( _doc, _this, "treshold" );
}


} // namespace noemixerr
