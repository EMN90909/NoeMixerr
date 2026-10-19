// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Danny McRae <khjklujn/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef _LADSPA_PORT_DIALOG_H
#define _LADSPA_PORT_DIALOG_H


#include <QDialog>

#include "LadspaManager.h"

namespace noemixerr::gui
{


class LadspaPortDialog : public QDialog
{
	Q_OBJECT
public:
	LadspaPortDialog( const ladspa_key_t & _key );
	~LadspaPortDialog() override = default;

};


} // namespace noemixerr::gui

#endif
