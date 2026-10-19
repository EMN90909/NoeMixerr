// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _LADSPA_BROWSER_H
#define _LADSPA_BROWSER_H

#include "LadspaManager.h"
#include "ToolPlugin.h"
#include "ToolPluginView.h"

namespace noemixerr
{


namespace gui
{


class TabBar;

class LadspaBrowserView : public ToolPluginView
{
	Q_OBJECT
public:
	LadspaBrowserView( ToolPlugin * _tool );
	~LadspaBrowserView() override = default;


public slots:
	void showPorts( const ::noemixerr::ladspa_key_t & _key );


private:
	TabBar * m_tabBar;

	QWidget * createTab( QWidget * _parent, const QString & _txt,
						LadspaPluginType _type );

};


} // namespace gui


class LadspaBrowser : public ToolPlugin
{
public:
	LadspaBrowser();
	~LadspaBrowser() override = default;

	gui::PluginView* instantiateView( QWidget * ) override
	{
		return new gui::LadspaBrowserView( this );
	}

	QString nodeName() const override;

	void saveSettings( QDomDocument& doc, QDomElement& element ) override
	{
		Q_UNUSED(doc)
		Q_UNUSED(element)
	}

	void loadSettings( const QDomElement& element ) override
	{
		Q_UNUSED(element)
	}


} ;


} // namespace noemixerr

#endif
