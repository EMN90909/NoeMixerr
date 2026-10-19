// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Danny McRae <khjklujn@netscape.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LADSPA_2_NoeMixerr_H
#define NoeMixerr_LADSPA_2_NoeMixerr_H

#include "LadspaManager.h"

namespace noemixerr
{

//! Class responsible for sorting found plugins (by LadspaManager)
//! into categories
class NOEMIXERR_EXPORT Ladspa2NoeMixerr : public LadspaManager
{
public:
	
	inline l_sortable_plugin_t getInstruments()
	{
		return( m_instruments );
	}
	
	inline l_sortable_plugin_t getValidEffects()
	{
		return( m_validEffects );
	}
	
	inline l_sortable_plugin_t getInvalidEffects()
	{
		return( m_invalidEffects );
	}
	
	inline l_sortable_plugin_t getAnalysisTools()
	{
		return( m_analysisTools );
	}
	
	inline l_sortable_plugin_t getOthers()
	{
		return( m_otherPlugins );
	}
	
	QString getShortName( const ladspa_key_t & _key );

private:
	Ladspa2NoeMixerr();
	~Ladspa2NoeMixerr() override = default;

	l_sortable_plugin_t m_instruments;
	l_sortable_plugin_t m_validEffects;
	l_sortable_plugin_t m_invalidEffects;
	l_sortable_plugin_t m_analysisTools;
	l_sortable_plugin_t m_otherPlugins;
	
	friend class Engine;

} ;


} // namespace noemixerr

#endif // NoeMixerr_LADSPA_2_NoeMixerr_H
