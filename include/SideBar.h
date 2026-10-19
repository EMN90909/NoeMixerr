// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SIDE_BAR_H
#define NoeMixerr_GUI_SIDE_BAR_H

#include <QMap>
#include <QButtonGroup>
#include <QToolBar>

class QToolButton;

namespace noemixerr::gui
{

class SideBarWidget;


class SideBar : public QToolBar
{
	Q_OBJECT
public:
	SideBar( Qt::Orientation _orientation, QWidget * _parent );
	~SideBar() override = default;

	void appendTab( SideBarWidget * _sbw );


private slots:
	void toggleButton( QAbstractButton * _btn );


private:
	QButtonGroup m_btnGroup;
	using ButtonMap = QMap<QToolButton*, QWidget*>;
	ButtonMap m_widgets;

} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_SIDE_BAR_H
