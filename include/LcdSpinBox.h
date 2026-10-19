// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LCD_SPINBOX_H
#define NoeMixerr_GUI_LCD_SPINBOX_H

#include "LcdWidget.h"
#include "AutomatableModelView.h"

namespace noemixerr::gui
{

class NoeMixerr_EXPORT LcdSpinBox : public LcdWidget, public IntModelView
{
	Q_OBJECT
public:
	LcdSpinBox( int numDigits, QWidget* parent, const QString& name = QString() );

	LcdSpinBox( int numDigits, const QString& style, QWidget* parent, const QString& name = QString() );

	~LcdSpinBox() override = default;

	void modelChanged() override
	{
		ModelView::modelChanged();
		update();
	}

	/*! Sets an offset which is always added to value of model so we can
	    display values in a user-friendly way if they internally start at 0 */
	void setDisplayOffset( int offset )
	{
		m_displayOffset = offset;
	}

	/*! \brief Returns internal offset for displaying values */
	int displayOffset() const
	{
		return m_displayOffset;
	}


public slots:
	virtual void update();


protected:
	void contextMenuEvent( QContextMenuEvent * _me ) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void mouseMoveEvent( QMouseEvent * _me ) override;
	void mouseReleaseEvent( QMouseEvent * _me ) override;
	void wheelEvent( QWheelEvent * _we ) override;
	void mouseDoubleClickEvent( QMouseEvent * _me ) override;

private:
	float m_remainder; //!< floating offset of spinbox in [-0.5, 0.5]
	bool m_mouseMoving;
	QPoint m_lastMousePos; //!< mouse position in last mouseMoveEvent
	int m_displayOffset;
	void enterValue();

signals:
	void manualChange();

} ;

using LcdSpinBoxModel = IntModel;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_LCD_SPINBOX_H
