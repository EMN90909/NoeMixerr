// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LADSPA_CONTROL_DIALOG_H
#define LADSPA_CONTROL_DIALOG_H

#include "EffectControlDialog.h"


class QHBoxLayout;

namespace noemixerr
{

class LadspaControls;


namespace gui
{


class LedCheckBox;


class LadspaControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	LadspaControlDialog( LadspaControls * _ctl );
	~LadspaControlDialog() override = default;


private slots:
	void updateEffectView( noemixerr::LadspaControls * _ctl );


private:
	QHBoxLayout * m_effectLayout;
	LedCheckBox * m_stereoLink;

} ;


} // namespace gui

} // namespace noemixerr

#endif
