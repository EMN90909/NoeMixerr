// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_CONTROLLER_DIALOG_H
#define NoeMixerr_GUI_CONTROLLER_DIALOG_H

#include <QWidget>

#include "ModelView.h"

namespace noemixerr
{

class Controller;

namespace gui
{

class ControllerDialog : public QWidget, public ModelView
{
public:
	ControllerDialog(Controller* controller, QWidget* parent);
	~ControllerDialog() override = default;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_CONTROLLER_DIALOG_H
