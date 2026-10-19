// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_AUTOMATABLE_SLIDER_H
#define NoeMixerr_GUI_AUTOMATABLE_SLIDER_H

#include <QSlider>

#include "AutomatableModelView.h"


namespace noemixerr::gui
{

class AutomatableSlider : public QSlider, public IntModelView
{
	Q_OBJECT
public:
	AutomatableSlider( QWidget * _parent, const QString & _name = QString() );
	~AutomatableSlider() override = default;

	bool showStatus()
	{
		return( m_showStatus );
	}


signals:
	void logicValueChanged( int _value );
	void logicSliderMoved( int _value );


protected:
	void contextMenuEvent( QContextMenuEvent * _me ) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void mouseReleaseEvent( QMouseEvent * _me ) override;
	void wheelEvent( QWheelEvent * _me ) override;
	void mouseDoubleClickEvent(QMouseEvent*) override;

	void modelChanged() override;


private:
	bool m_showStatus;
	void enterValue();


private slots:
	void changeValue( int _value );
	void moveSlider( int _value );
	void updateSlider();

} ;


using sliderModel = IntModel;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_AUTOMATABLE_SLIDER_H
