// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TOOL_PLUGIN_VIEW_H
#define NoeMixerr_GUI_TOOL_PLUGIN_VIEW_H

#include "PluginView.h"

namespace noemixerr
{

class ToolPlugin;

namespace gui
{


class NOEMIXERR_EXPORT ToolPluginView : public PluginView
{
public:
	ToolPluginView( ToolPlugin * _toolPlugin );

} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_TOOL_PLUGIN_VIEW_H
