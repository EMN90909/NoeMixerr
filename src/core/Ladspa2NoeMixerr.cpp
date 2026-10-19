// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Danny McRae <khjklujn@netscape.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "Ladspa2NoeMixerr.h"


namespace noemixerr
{


Ladspa2NoeMixerr::Ladspa2NoeMixerr()
{
	l_sortable_plugin_t plugins = getSortedPlugins();
	
	for (const auto& plugin : plugins)
	{
		ladspa_key_t key = plugin.second;
		LadspaManagerDescription * desc = getDescription( key );
		
		if( desc->type == LadspaPluginType::Source )
		{
			m_instruments.append( qMakePair( getName( key ), 
								key ) );
		}
		else if( desc->type == LadspaPluginType::Transfer &&
			( desc->inputChannels == desc->outputChannels &&
			( desc->inputChannels == 1 ||
			desc->inputChannels == 2 ||
			desc->inputChannels == 4 )/* &&
			isRealTimeCapable( key )*/ ) )
		{
			m_validEffects.append( qMakePair( getName( key ),
								key ) );
		}
		else if( desc->type == LadspaPluginType::Transfer &&
			( desc->inputChannels != desc->outputChannels ||
			( desc->inputChannels != 1 &&
			desc->inputChannels != 2 &&
			desc->inputChannels != 4 ) ||
			!isRealTimeCapable( key ) ) )
		{
			m_invalidEffects.append( qMakePair( getName( key ), 
								key ) );
		}
		else if( desc->type == LadspaPluginType::Sink )
		{
			m_analysisTools.append( qMakePair( getName( key ),
								key ) );
		}
		else if( desc->type == LadspaPluginType::Other )
		{
			m_otherPlugins.append( qMakePair( getName( key ), 
								key ) );
		}
	}
}
 
 
 
 
QString Ladspa2NoeMixerr::getShortName( const ladspa_key_t & _key )
{
	QString name = getName( _key );
	
	if( name.indexOf( "(" ) > 0 )
	{
		name = name.left( name.indexOf( "(" ) );
	}
	if( name.indexOf( " - " ) > 0 )
	{
		name = name.left( name.indexOf( " - " ) );
	}
	if( name.indexOf( "  " ) > 0 )
	{
		name = name.left( name.indexOf( "  " ) );
	}
	Qt::CaseSensitivity cs = Qt::CaseInsensitive;
	if( name.indexOf( " with ", 0, cs ) > 0 )
	{
		name = name.left( name.indexOf( " with ", 0, cs ) );
	}
	if( name.indexOf( ",", 0, cs ) > 0 )
	{
		name = name.left( name.indexOf( ",", 0, cs ) );
	}
	if( name.length() > 40 )
	{
		int i = 40;
		while( name[i] != ' ' && i > 0 )
		{
			i--;
		}
		name = name.left( i );
	}
	if( name.length() == 0 )
	{
		name = "LADSPA Plugin";
	}
	
	return name;
}



} // namespace noemixerr
