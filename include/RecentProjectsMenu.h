// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2022 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_RECENT_PROJECTS_MENU_H
#define NoeMixerr_GUI_RECENT_PROJECTS_MENU_H

#include <QMenu>

namespace noemixerr::gui
{


class RecentProjectsMenu : public QMenu
{
	Q_OBJECT
public:
	RecentProjectsMenu(QWidget *parent = nullptr);

private slots:
	void fillMenu();
	void openProject(QAction * _action );
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_RECENT_PROJECTS_MENU_H
