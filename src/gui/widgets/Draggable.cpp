// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Draggable.h"
#include "SimpleTextFloat.h"
#include "interpolation.h"

#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>

namespace noemixerr::gui
{

Draggable::Draggable(DirectionOfManipulation directionOfManipulation, 
	FloatModel* floatModel, const QPixmap& pixmap, int pointA, int pointB, QWidget* parent)
	: FloatModelEditorBase(directionOfManipulation, parent),
	  m_pixmap(pixmap),
	  m_defaultValPixmap(),
	  m_pointA(pointA),
	  m_pointB(pointB),
	  m_defaultValue(0),
	  m_hasDefaultValPixmap(false)
{
	setModel(floatModel);
	connect(model(), &FloatModel::dataChanged, this, &Draggable::handleMovement);
	handleMovement();
}

QSize Draggable::sizeHint() const
{
	return m_pixmap.size();
}

void Draggable::setPixmap(const QPixmap& pixmap)
{
	m_pixmap = pixmap;
	update();
}

void Draggable::setDefaultValPixmap(const QPixmap& pixmap, float value)
{
	m_defaultValPixmap = pixmap;
	m_defaultValue = value;
	m_hasDefaultValPixmap = true;
	update();
}

void Draggable::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	
	if (m_hasDefaultValPixmap && model()->value() == m_defaultValue)
	{
		painter.drawPixmap(rect(), m_defaultValPixmap, m_defaultValPixmap.rect());
	}
	else
	{
		painter.drawPixmap(rect(), m_pixmap, m_pixmap.rect());
	}
}

void Draggable::mouseMoveEvent(QMouseEvent* me)
{
	updateInteractionState(me);

	QPoint pPos = mapToParent(me->pos());
	if (currentInteraction() == InteractionType::MouseDrag && pPos != m_lastMousePos)
	{
		float point = (directionOfManipulation() == DirectionOfManipulation::Vertical) ? pPos.y() : pPos.x();
		float progress = (point - m_pointA) / (m_pointB - m_pointA);

		if (progress >= 0 && progress <= 1)
		{
			float newVal = progress * (model()->maxValue() - model()->minValue()) + model()->minValue();
			model()->setValue(newVal);
		}
		else if (progress < 0)
		{
			model()->setValue(model()->minValue());
		}
		else
		{
			model()->setValue(model()->maxValue());
		}

		emit sliderMoved(model()->value());
		m_lastMousePos = pPos;

		showTextFloat();
	}
}

void Draggable::handleMovement()
{
	float newCoord = std::lerp(m_pointA, m_pointB, (model()->value() - model()->minValue()) / (model()->maxValue() - model()->minValue()));
	if (directionOfManipulation() == DirectionOfManipulation::Vertical)
	{
		move(x(), newCoord - m_pixmap.height() / 2.f);
	}
	else if (directionOfManipulation() == DirectionOfManipulation::Horizontal)
	{
		move(newCoord - m_pixmap.width() / 2.f, y());
	}
}

} // namespace noemixerr::gui
