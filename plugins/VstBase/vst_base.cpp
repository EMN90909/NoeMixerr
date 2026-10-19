// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "NoeMixerrCommonMacros.h"
#include "Plugin.h"
#include "vstbase_export.h"

namespace noemixerr
{


extern "C"
{

Plugin::Descriptor VSTBASE_EXPORT vstbase_plugin_descriptor =
{
	NoeMixerr_STRINGIFY( PLUGIN_NAME ),
	"VST Base",
	"library for all NoeMixerr plugins dealing with VST-plugins",
	"Tobias Doerffel <tobydox/at/users/dot/sf/dot/net>",
	0x0100,
	Plugin::Type::Library,
	nullptr,
	nullptr,
} ;

}


} // namespace noemixerr
