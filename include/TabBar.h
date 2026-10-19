// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TAB_BAR_H
#define NoeMixerr_GUI_TAB_BAR_H

#include <QBoxLayout>
#include <QMap>
#include <QWidget>

#include "noemixerr_export.h"


namespace noemixerr::gui
{


class TabButton;


class NoeMixerr_EXPORT TabBar : public QWidget
{
	Q_OBJECT
public:
	TabBar( QWidget * _parent,
			QBoxLayout::Direction _dir = QBoxLayout::LeftToRight );
	~TabBar() override = default;

	TabButton * addTab( QWidget * _w, const QString & _text,
					int _id, bool _add_stretch = false,
					bool _text_is_tooltip = false,
					// TODO Remove fixWidgetToParentSize once it is used
					//      with false everywhere.
					//      At the time of writing it is only used in
					//      LadspaBrowser with default parameters.
					bool fixWidgetToParentSize = true );
	void removeTab( int _id );

	inline void setExclusive( bool _on )
	{
		m_exclusive = _on;
	}

	int activeTab();


public slots:
	void setActiveTab( int _id );


protected:
	bool tabState( int _id );
	void setTabState( int _id, bool _checked );
	bool allHidden();


protected slots:
	void hideAll( int _exception = -1 );
	void tabClicked( int _id );


private:
	QMap<int, QPair<TabButton *, QWidget *> > m_tabs;
	QBoxLayout * m_layout;
	bool m_exclusive;


signals:
	void allWidgetsHidden();
	void widgetShown();

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TAB_BAR_H
