// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 
#ifndef NoeMixerr_GUI_DRAGGABLE_H
#define NoeMixerr_GUI_DRAGGABLE_H

#include "FloatModelEditorBase.h"

namespace noemixerr::gui
{

/**
 * @brief A pixmap that can be dragged from one location to another to control a FloatModel
 */
class NoeMixerr_EXPORT Draggable : public FloatModelEditorBase
{
	Q_OBJECT

public:
	using FloatModelEditorBase::DirectionOfManipulation;
	
	/**
	 * @param directionOfManipulation Direction the user can drag the control
	 * @param floatModel Pointer to the FloatModel this draggable modifies
	 * @param pixmap The pixmap shown for this handle
	 * @param pointA Starting pixel position (Y if vertical, X if horizontal)
	 * @param pointB Ending pixel position (Y if vertical, X if horizontal)
	 * @param parent Parent QWidget
	 */
	Draggable(DirectionOfManipulation directionOfManipulation,
		FloatModel* floatModel, const QPixmap& pixmap, int pointA, int pointB, QWidget* parent = nullptr);

	QSize sizeHint() const override;
	void setPixmap(const QPixmap& pixmap);
	void setDefaultValPixmap(const QPixmap& pixmap, float value = 0.f);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* me) override;

protected slots:
	void handleMovement();

private:
	QPixmap m_pixmap;
	QPixmap m_defaultValPixmap;
	float m_pointA;
	float m_pointB;
	float m_defaultValue;
	bool m_hasDefaultValPixmap;
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_DRAGGABLE_H
