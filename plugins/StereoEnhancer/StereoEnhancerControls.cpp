// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.




#include "StereoEnhancerControls.h"
#include "StereoEnhancer.h"

namespace noemixerr
{


StereoEnhancerControls::StereoEnhancerControls( StereoEnhancerEffect * _eff ) :
		EffectControls( _eff ),
		m_effect( _eff ),
		m_widthModel(0.0f, 0.0f, 180.0f, 1.0f, this, tr( "Width" ) )
{
	connect( &m_widthModel, SIGNAL( dataChanged() ),
			this, SLOT( changeWideCoeff() ) );

	changeWideCoeff();
}



void StereoEnhancerControls::changeWideCoeff()
{
	m_effect->m_seFX.setWideCoeff( m_widthModel.value() );
}



void StereoEnhancerControls::loadSettings( const QDomElement & _this )
{
	m_widthModel.loadSettings( _this, "width" );
}




void StereoEnhancerControls::saveSettings( QDomDocument & _doc, 
							QDomElement & _this )
{
	m_widthModel.saveSettings( _doc, _this, "width" );
}


} // namespace noemixerr
