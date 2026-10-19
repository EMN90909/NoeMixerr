// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) LMMS team
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "SimpleTextFloat.h"

#include <QTimer>
#include <QHBoxLayout>
#include <QLabel>

#include "GuiApplication.h"
#include "MainWindow.h"

namespace noemixerr::gui
{


SimpleTextFloat::SimpleTextFloat() :
	QWidget(getGUI()->mainWindow(), Qt::ToolTip)
{
	QHBoxLayout * layout = new QHBoxLayout(this);
	layout->setContentsMargins(3, 3, 3, 3);
	setLayout(layout);

	m_textLabel = new QLabel(this);
	layout->addWidget(m_textLabel);

	m_showTimer = new QTimer(this);
	m_showTimer->setSingleShot(true);
	QObject::connect(m_showTimer, &QTimer::timeout, this, &SimpleTextFloat::show);

	m_hideTimer = new QTimer(this);
	m_hideTimer->setSingleShot(true);
	QObject::connect(m_hideTimer, &QTimer::timeout, this, &SimpleTextFloat::hide);
}

void SimpleTextFloat::setText(const QString & text)
{
	m_textLabel->setText(text);
}

void SimpleTextFloat::showWithDelay(int msecBeforeDisplay, int msecDisplayTime)
{
	if (msecBeforeDisplay > 0)
	{
		m_showTimer->start(msecBeforeDisplay);
	}
	else
	{
		show();
	}

	if (msecDisplayTime > 0)
	{
		m_hideTimer->start(msecBeforeDisplay + msecDisplayTime);
	}
}

void SimpleTextFloat::show()
{
	QWidget::show();
}

void SimpleTextFloat::hide()
{
	m_source = nullptr;
	m_showTimer->stop();
	m_hideTimer->stop();
	QWidget::hide();
}

} // namespace noemixerr::gui
