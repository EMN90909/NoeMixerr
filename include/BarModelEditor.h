// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023-now Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#pragma once

#ifndef NoeMixerr_GUI_BAR_MODEL_EDITOR_H
#define NoeMixerr_GUI_BAR_MODEL_EDITOR_H

#include "FloatModelEditorBase.h"


namespace noemixerr::gui
{

class NOEMIXERR_EXPORT BarModelEditor : public FloatModelEditorBase
{
	Q_OBJECT

public:
	Q_PROPERTY(QBrush backgroundBrush READ getBackgroundBrush WRITE setBackgroundBrush)
	Q_PROPERTY(QBrush barBrush READ getBarBrush WRITE setBarBrush)
	Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

	BarModelEditor(QString text, FloatModel * floatModel, QWidget * parent = nullptr);

	// Define how the widget will behave in a layout
	QSizePolicy sizePolicy() const;

	QSize minimumSizeHint() const override;

	QSize sizeHint() const override;

	QBrush const & getBackgroundBrush() const;
	void setBackgroundBrush(QBrush const & backgroundBrush);

	QBrush const & getBarBrush() const;
	void setBarBrush(QBrush const & barBrush);

	QColor const & getTextColor() const;
	void setTextColor(QColor const & textColor);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	QString const m_text;

	QBrush m_backgroundBrush;
	QBrush m_barBrush;
	QColor m_textColor;
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_BAR_MODEL_EDITOR_H
