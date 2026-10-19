// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_CPU_LOAD_WIDGET_H
#define NoeMixerr_GUI_CPU_LOAD_WIDGET_H

#include <algorithm>
#include <QTimer>
#include <QPixmap>
#include <QWidget>

#include "NoeMixerrTypes.h"


namespace noemixerr::gui
{


class CPULoadWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(int stepSize MEMBER m_stepSize)
public:
	CPULoadWidget( QWidget * _parent );
	~CPULoadWidget() override = default;


protected:
	void paintEvent( QPaintEvent * _ev ) override;


protected slots:
	void updateCpuLoad();


private:
	int stepSize() const { return std::max(1, m_stepSize); }

	int m_currentLoad;

	QPixmap m_temp;
	QPixmap m_background;
	QPixmap m_leds;

	bool m_changed;

	QTimer m_updateTimer;

	int m_stepSize = 1;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_CPU_LOAD_WIDGET_H
