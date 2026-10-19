// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "ToolPlugin.h"


namespace noemixerr
{


ToolPlugin::ToolPlugin( const Descriptor * _descriptor, Model * _parent ) :
	Plugin( _descriptor, _parent )
{
}




ToolPlugin * ToolPlugin::instantiate( const QString & _plugin_name, Model * _parent )
{
	Plugin * p = Plugin::instantiate( _plugin_name, _parent, nullptr );
	// check whether instantiated plugin is a tool
	if( p->type() == Plugin::Type::Tool )
	{
		// everything ok, so return pointer
		return dynamic_cast<ToolPlugin *>( p );
	}

	// not quite... so delete plugin
	delete p;
	return nullptr;
}


} // namespace noemixerr