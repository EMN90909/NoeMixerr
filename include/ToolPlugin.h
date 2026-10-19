// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_TOOL_PLUGIN_H
#define NoeMixerr_TOOL_PLUGIN_H

#include "Plugin.h"


namespace noemixerr
{


class NoeMixerr_EXPORT ToolPlugin : public Plugin
{
public:
	ToolPlugin( const Descriptor * _descriptor, Model * _parent );
	~ToolPlugin() override = default;

	// instantiate tool-plugin with given name or return NULL
	// on failure
	static ToolPlugin * instantiate( const QString & _plugin_name,
										Model * _parent );

} ;


} // namespace noemixerr

#endif // NoeMixerr_TOOL_PLUGIN_H
