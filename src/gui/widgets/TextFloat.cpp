// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "TextFloat.h"

#include <QTimer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "GuiApplication.h"
#include "MainWindow.h"

namespace noemixerr::gui
{


TextFloat::TextFloat() :
	TextFloat("", "", QPixmap())
{
}

TextFloat::TextFloat(const QString & title, const QString & text, const QPixmap & pixmap) :
	QWidget(getGUI()->mainWindow(), Qt::ToolTip)
{
	QHBoxLayout * mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	// Create the label that displays the pixmap
	m_pixmapLabel = new QLabel(this);
	mainLayout->addWidget(m_pixmapLabel);

	// Create the widget that displays the title and the text
	QWidget * titleAndTextWidget = new QWidget(this);
	QVBoxLayout * titleAndTextLayout = new QVBoxLayout();
	titleAndTextWidget->setLayout(titleAndTextLayout);

	m_titleLabel = new QLabel(titleAndTextWidget);
	m_titleLabel->setStyleSheet("font-weight: bold;");
	titleAndTextLayout->addWidget(m_titleLabel);

	m_textLabel = new QLabel(titleAndTextWidget);
	titleAndTextLayout->addWidget(m_textLabel);

	mainLayout->addWidget(titleAndTextWidget);

	// Call the setters so that the hidden state is updated
	setTitle(title);
	setText(text);
	setPixmap(pixmap);
}

void TextFloat::setTitle(const QString & title)
{
	m_titleLabel->setText(title);
	m_titleLabel->setHidden(title.isEmpty());
}

void TextFloat::setText(const QString & text)
{
	m_textLabel->setText(text);
	m_textLabel->setHidden(text.isEmpty());
}

void TextFloat::setPixmap(const QPixmap & pixmap)
{
	m_pixmapLabel->setPixmap(pixmap);
	m_pixmapLabel->setHidden(pixmap.isNull());
}

void TextFloat::setVisibilityTimeOut(int msecs)
{
	QTimer::singleShot(msecs, this, SLOT(hide()));
	show();
}

TextFloat * TextFloat::displayMessage(const QString & title,
					const QString & msg,
					const QPixmap & pixmap,
					int timeout, QWidget * parent)
{
	auto tf = new TextFloat(title, msg, pixmap);

	// Show the widget so that the correct height is calculated in the code that follows
	tf->show();

	if(parent != nullptr)
	{
		tf->moveGlobal(parent, QPoint(parent->width() + 2, 0));
	}
	else
	{
		// If no parent is given move the window to the lower left area of the main window
		QWidget * mw = getGUI()->mainWindow();
		tf->moveGlobal(mw, QPoint(32, mw->height() - tf->height() - 8));
	}

	if (timeout > 0)
	{
		tf->setAttribute(Qt::WA_DeleteOnClose, true);
		QTimer::singleShot(timeout, tf, SLOT(close()));
	}

	return tf;
}

void TextFloat::mousePressEvent(QMouseEvent *)
{
	close();
}

} // namespace noemixerr::gui
