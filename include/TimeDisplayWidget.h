// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Ruben Ibarra
// Copyright (c) 2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TIME_DISPLAY_WIDGET_H
#define NoeMixerr_GUI_TIME_DISPLAY_WIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include "LcdWidget.h"

namespace noemixerr::gui
{

class TimeDisplayWidget : public QWidget
{
	Q_OBJECT
public:
	TimeDisplayWidget();
	~TimeDisplayWidget() override = default;


protected:
	void mousePressEvent( QMouseEvent* mouseEvent ) override;


private slots:
	void updateTime();


private:
	enum class DisplayMode
	{
		MinutesSeconds,
		BarsTicks
	};

	void setDisplayMode( DisplayMode displayMode );

	DisplayMode m_displayMode;
	QHBoxLayout m_spinBoxesLayout;
	LcdWidget m_majorLCD;
	LcdWidget m_minorLCD;
	LcdWidget m_milliSecondsLCD;

} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TIME_DISPLAY_WIDGET_H
