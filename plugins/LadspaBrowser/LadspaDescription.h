// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef _LADSPA_DESCRIPTION_H
#define _LADSPA_DESCRIPTION_H


#include <QWidget>

#include "LadspaManager.h"


class QListWidgetItem;
class QScrollArea;

namespace noemixerr::gui
{


class LadspaDescription : public QWidget
{
	Q_OBJECT
public:
	LadspaDescription( QWidget * _parent, LadspaPluginType _type );
	~LadspaDescription() override = default;


signals:
	void doubleClicked( const ::noemixerr::ladspa_key_t & );


private:
	QScrollArea * m_scrollArea;

	QList<ladspa_key_t> m_pluginKeys;
	ladspa_key_t m_currentSelection;

	void update( const ladspa_key_t & _key );


private slots:
	void rowChanged( int _pluginIndex );
	void onDoubleClicked( QListWidgetItem * _item );

} ;


} // namespace noemixerr::gui

#endif
