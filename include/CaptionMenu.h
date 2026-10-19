// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007-2008 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_CAPTION_MENU_H
#define NoeMixerr_GUI_CAPTION_MENU_H

#include <QMenu>

#include "noemixerr_export.h"

namespace noemixerr::gui
{

///
/// \brief A context menu with a caption
///
class NOEMIXERR_EXPORT CaptionMenu : public QMenu
{
	Q_OBJECT
public:
	CaptionMenu( const QString & _title, QWidget * _parent = 0 );
	~CaptionMenu() override = default;
} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_CAPTION_MENU_H
