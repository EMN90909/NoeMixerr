// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/yahoo.com>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_METER_DIALOG_H
#define NoeMixerr_GUI_METER_DIALOG_H

#include <QWidget>

#include "ModelView.h"

namespace noemixerr::gui
{

class LcdSpinBox;


class MeterDialog : public QWidget, public ModelView
{
	Q_OBJECT
public:
	MeterDialog( QWidget * _parent, bool _simple = false );
	~MeterDialog() override = default;

	void modelChanged() override;


private:
	LcdSpinBox * m_numerator;
	LcdSpinBox * m_denominator;

} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_METER_DIALOG_H
