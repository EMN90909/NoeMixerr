// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.




#include "StereoMatrixControls.h"
#include "StereoMatrix.h"

namespace noemixerr
{


StereoMatrixControls::StereoMatrixControls( StereoMatrixEffect * _eff ) :
		EffectControls( _eff ),
		m_effect( _eff ),
		m_llModel( 1.0f, -1.0f, 1.0f, 0.01f, this, tr( "Left to Left" ) ),
		m_lrModel( 0.0f, -1.0f, 1.0f, 0.01f, this, tr( "Left to Right" ) ),
		m_rlModel( 0.0f, -1.0f, 1.0f, 0.01f, this, tr( "Right to Left" ) ),
		m_rrModel( 1.0f, -1.0f, 1.0f, 0.01f, this, tr( "Right to Right" ) )
{
	m_llModel.setCenterValue( 0 );
	m_lrModel.setCenterValue( 0 );
	m_rlModel.setCenterValue( 0 );
	m_rrModel.setCenterValue( 0 );

	connect( &m_llModel, SIGNAL( dataChanged() ),
			this, SLOT( changeMatrix() ) );
	connect( &m_lrModel, SIGNAL( dataChanged() ),
			this, SLOT( changeMatrix() ) );
	connect( &m_rlModel, SIGNAL( dataChanged() ),
			this, SLOT( changeMatrix() ) );
	connect( &m_rrModel, SIGNAL( dataChanged() ),
			this, SLOT( changeMatrix() ) );

	changeMatrix();
}



void StereoMatrixControls::changeMatrix()
{
}



void StereoMatrixControls::loadSettings( const QDomElement & _this )
{
	m_llModel.loadSettings( _this, "l-l" );
	m_lrModel.loadSettings( _this, "l-r" );
	m_rlModel.loadSettings( _this, "r-l" );
	m_rrModel.loadSettings( _this, "r-r" );
}




void StereoMatrixControls::saveSettings( QDomDocument & _doc, 
							QDomElement & _this )
{
	m_llModel.saveSettings( _doc, _this, "l-l" );
	m_lrModel.saveSettings( _doc, _this, "l-r" );
	m_rlModel.saveSettings( _doc, _this, "r-l" );
	m_rrModel.saveSettings( _doc, _this, "r-r" );
}


} // namespace noemixerr