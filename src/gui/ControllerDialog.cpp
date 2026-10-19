// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "ControllerDialog.h"

#include "Controller.h"

namespace noemixerr::gui
{

ControllerDialog::ControllerDialog(Controller* controller, QWidget* parent)
	: QWidget{parent}
	, ModelView{controller, this}
{
}

} // namespace noemixerr::gui
