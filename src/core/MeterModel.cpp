// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "MeterModel.h"
#include "AutomationClip.h"


namespace noemixerr
{

MeterModel::MeterModel( Model * _parent ) :
	Model( _parent ),
	m_numeratorModel( 4, 1, 32, this, tr( "Numerator" ) ),
	m_denominatorModel( 4, 1, 32, this, tr( "Denominator" ) )
{
	connect( &m_numeratorModel, SIGNAL(dataChanged()), 
			this, SIGNAL(dataChanged()), Qt::DirectConnection );
	connect( &m_denominatorModel, SIGNAL(dataChanged()), 
			this, SIGNAL(dataChanged()), Qt::DirectConnection );
}


void MeterModel::reset()
{
	m_numeratorModel.setValue( 4 );
	m_denominatorModel.setValue( 4 );

	AutomationClip::globalAutomationClip( &m_numeratorModel )->clear();
	AutomationClip::globalAutomationClip( &m_denominatorModel )->clear();
}




void MeterModel::saveSettings( QDomDocument & _doc, QDomElement & _this,
								const QString & _name )
{
	m_numeratorModel.saveSettings( _doc, _this, _name + "_numerator" );
	m_denominatorModel.saveSettings( _doc, _this, _name + "_denominator" );
}




void MeterModel::loadSettings( const QDomElement & _this,
								const QString & _name )
{
	m_numeratorModel.loadSettings( _this, _name + "_numerator" );
	m_denominatorModel.loadSettings( _this, _name + "_denominator" );
}


} // namespace noemixerr
