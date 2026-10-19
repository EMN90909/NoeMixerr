// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2015 Colin Wallace <wallacoloo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LEFT_RIGHT_NAV_H
#define NoeMixerr_GUI_LEFT_RIGHT_NAV_H

#include <QPushButton>


namespace noemixerr::gui
{

class LeftRightNav : public QWidget
{
	Q_OBJECT
public:
	LeftRightNav(QWidget *parent=nullptr);
	void setShortcuts(const QKeySequence &leftShortcut=Qt::Key_Minus, const QKeySequence &rightShortcut=Qt::Key_Plus);
signals:
	void onNavLeft();
	void onNavRight();
private:
	QHBoxLayout m_layout;
	QPushButton m_leftBtn;
	QPushButton m_rightBtn;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_LEFT_RIGHT_NAV_H
