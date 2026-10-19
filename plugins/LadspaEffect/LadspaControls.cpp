// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QDomElement>

#include "LadspaBase.h"
#include "LadspaControl.h"
#include "LadspaEffect.h"

namespace noemixerr
{


LadspaControls::LadspaControls( LadspaEffect * _eff ) :
	EffectControls( _eff ),
	m_effect( _eff ),
	m_processors( _eff->processorCount() ),
	m_noLink( false ),
	m_stereoLinkModel( true, this )
{

	connect( &m_stereoLinkModel, SIGNAL( dataChanged() ),
				this, SLOT( updateLinkStatesFromGlobal() ),
				Qt::DirectConnection );

	multi_proc_t controls = m_effect->getPortControls();
	m_controlCount = controls.count();

	for( ch_cnt_t proc = 0; proc < m_processors; proc++ )
	{
		control_list_t p;

		const bool linked_control = ( m_processors > 1 && proc == 0 );

		for (const auto& control : controls)
		{
			if (control->proc == proc)
			{
				control->control = new LadspaControl(this, control, linked_control);

				p.append(control->control);

				if (linked_control)
				{
					connect(control->control, SIGNAL(linkChanged(int, bool)),
								this, SLOT(linkPort(int, bool)),
								Qt::DirectConnection);
				}
			}
		}

		m_controls.append( p );
	}

	// now link all controls
	if( m_processors > 1 )
	{
		for (const auto& control : controls)
		{
			if (control->proc == 0)
			{
				linkPort(control->control_id, true);
			}
		}
	}
}




LadspaControls::~LadspaControls()
{
	for( ch_cnt_t proc = 0; proc < m_processors; proc++ )
	{
		m_controls[proc].clear();
	}
	m_controls.clear();
}




void LadspaControls::saveSettings( QDomDocument & _doc, QDomElement & _this )
{
	if( m_processors > 1 )
	{
		_this.setAttribute( "link", m_stereoLinkModel.value() );
	}
	
	multi_proc_t controls = m_effect->getPortControls();
	_this.setAttribute( "ports", controls.count() );
	for (const auto& control : controls)
	{
		QString n = "port" + QString::number(control->proc) + QString::number(control->port_id);
		control->control->saveSettings(_doc, _this, n);
	}
}




void LadspaControls::loadSettings( const QDomElement & _this )
{
	if( m_processors > 1 )
	{
		m_stereoLinkModel.setValue( _this.attribute( "link" ).toInt() );
	}
	
	multi_proc_t controls = m_effect->getPortControls();
	for (const auto& control : controls)
	{
		QString n = "port" + QString::number(control->proc) + QString::number(control->port_id);
		control->control->loadSettings(_this, n);
	}
}




void LadspaControls::linkPort( int _port, bool _state )
{
	LadspaControl * first = m_controls[0][_port];
	if( _state )
	{
		for( ch_cnt_t proc = 1; proc < m_processors; proc++ )
		{
			first->linkControls( m_controls[proc][_port] );
		}
	}
	else
	{
		for( ch_cnt_t proc = 1; proc < m_processors; proc++ )
		{
			first->unlinkControls( m_controls[proc][_port] );
		}

		// m_stereoLinkModel.setValue() will call updateLinkStatesFromGlobal()
		// m_noLink will make sure that this will not unlink any other ports
		m_noLink = true;
		m_stereoLinkModel.setValue( false );
	}
}



void LadspaControls::updateLinkStatesFromGlobal()
{
	if( m_stereoLinkModel.value() )
	{
		for( int port = 0; port < m_controlCount / m_processors; port++ )
		{
			m_controls[0][port]->setLink( true );
		}
	}
	else if( !m_noLink )
	{
		for( int port = 0; port < m_controlCount / m_processors; port++ )
		{
			m_controls[0][port]->setLink( false );
		}
	}

	// if global channel link state has changed, always ignore link
	// status of individual ports in the future
	m_noLink = false;
}


} // namespace noemixerr
