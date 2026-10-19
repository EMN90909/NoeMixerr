// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_PLUGIN_VIEW_H
#define NoeMixerr_GUI_PLUGIN_VIEW_H

#include <QWidget>

#include "ModelView.h"
#include "Plugin.h"

namespace noemixerr::gui {

class NoeMixerr_EXPORT PluginView : public QWidget, public ModelView
{
public:
	PluginView(Plugin* _plugin, QWidget* _parent)
		: QWidget(_parent)
		, ModelView(_plugin, this)
	{
	}

	virtual bool isResizable() const { return false; }
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_PLUGIN_VIEW_H
