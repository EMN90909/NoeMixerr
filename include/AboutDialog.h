// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_ABOUT_DIALOG_H
#define NoeMixerr_GUI_ABOUT_DIALOG_H

#include <QDialog>

#include "ui_about_dialog.h"

namespace noemixerr::gui
{

class AboutDialog : public QDialog, public Ui::AboutDialog
{
public:
	AboutDialog(QWidget* parent=0);

} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_ABOUT_DIALOG_H
