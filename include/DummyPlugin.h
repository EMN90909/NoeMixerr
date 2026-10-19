// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_DUMMY_PLUGIN_H
#define NoeMixerr_DUMMY_PLUGIN_H

#include "Plugin.h"
#include "PluginView.h"


namespace noemixerr
{

class DummyPlugin : public Plugin
{
public:
	DummyPlugin() :
		Plugin( nullptr, nullptr )
	{
	}

	~DummyPlugin() override = default;

	void saveSettings( QDomDocument &, QDomElement & ) override
	{
	}

	void loadSettings( const QDomElement & ) override
	{
	}

	QString nodeName() const override
	{
		return "DummyPlugin";
	}


protected:
	gui::PluginView * instantiateView( QWidget * _parent ) override
	{
		return new gui::PluginView( this, _parent );
	}

} ;


} // namespace noemixerr

#endif // NoeMixerr_DUMMY_PLUGIN_H
