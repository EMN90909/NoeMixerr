// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2022 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TEMPLATES_MENU_H
#define NoeMixerr_GUI_TEMPLATES_MENU_H

#include <QDir>
#include <QMenu>


namespace noemixerr::gui
{


class TemplatesMenu : public QMenu
{
	Q_OBJECT
public:
	TemplatesMenu(QWidget *parent = nullptr);
	~TemplatesMenu() override = default;

private slots:
	static void createNewProjectFromTemplate(QAction * _action);
	void fillTemplatesMenu();
	void addTemplatesFromDir( const QDir& dir );

};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TEMPLATES_MENU_H
