// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LADSPA_CONTROL_VIEW_H
#define NoeMixerr_GUI_LADSPA_CONTROL_VIEW_H

#include <QWidget>

#include "ModelView.h"

namespace noemixerr
{

class LadspaControl;

namespace gui
{

class NoeMixerr_EXPORT LadspaControlView : public QWidget, public ModelView
{
	Q_OBJECT
public:
	LadspaControlView( QWidget * _parent, LadspaControl * _ctl );
	~LadspaControlView() override = default;

private:
	LadspaControl * m_ctl;

} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_LADSPA_CONTROL_VIEW_H
