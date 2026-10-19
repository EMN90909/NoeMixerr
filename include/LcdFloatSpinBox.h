// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2020 Martin Pavelek <he29.HS/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LCD_FLOATSPINBOX_H
#define NoeMixerr_GUI_LCD_FLOATSPINBOX_H

#include <QString>

#include "LcdWidget.h"
#include "AutomatableModelView.h"

namespace noemixerr::gui
{


class NOEMIXERR_EXPORT LcdFloatSpinBox : public QWidget, public FloatModelView
{
	Q_OBJECT
public:
	LcdFloatSpinBox(int numWhole, int numFrac, const QString& name = QString(), QWidget* parent = nullptr);
	LcdFloatSpinBox(int numWhole, int numFrac, const QString& style, const QString& name, QWidget* parent = nullptr);

	void modelChanged() override
	{
		ModelView::modelChanged();
		update();
	}

	void setLabel(const QString &label) { m_label = label; }
	
	void setSeamless(bool left, bool right)
	{
		m_wholeDisplay.setSeamless(left, true);
		m_fractionDisplay.setSeamless(true, right);
	}

public slots:
	virtual void update();

protected:
	void contextMenuEvent(QContextMenuEvent *me) override;
	void mousePressEvent(QMouseEvent *me) override;
	void mouseMoveEvent(QMouseEvent *me) override;
	void mouseReleaseEvent(QMouseEvent *me) override;
	void wheelEvent(QWheelEvent *we) override;
	void mouseDoubleClickEvent(QMouseEvent *me) override;
	void paintEvent(QPaintEvent *pe) override;

private:
	void layoutSetup(const QString &style = QString("19green"));
	void enterValue();
	float getStep() const;

	LcdWidget m_wholeDisplay;
	LcdWidget m_fractionDisplay;
	bool m_mouseMoving;
	bool m_intStep;
	QPoint m_origMousePos;
	int m_displayOffset;
	QString m_label;

signals:
	void manualChange();

};

using LcdFloatSpinBoxModel = FloatModel;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_LCD_FLOATSPINBOX_H
