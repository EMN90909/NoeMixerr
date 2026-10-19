// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 LMMS team
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SIMPLE_TEXT_FLOAT_H
#define NoeMixerr_GUI_SIMPLE_TEXT_FLOAT_H

#include <QWidget>

#include "noemixerr_export.h"

class QLabel;
class QTimer;

namespace noemixerr::gui
{

class NoeMixerr_EXPORT SimpleTextFloat : public QWidget
{
	Q_OBJECT
public:
	SimpleTextFloat();
	~SimpleTextFloat() override = default;

	void setText(const QString & text);

	void showWithDelay(int msecBeforeDisplay, int msecDisplayTime);

	void showWithTimeout(int msec)
	{
		showWithDelay(0, msec);
	}

	void moveGlobal(QWidget * w, const QPoint & offset)
	{
		move(w->mapToGlobal(QPoint(0, 0)) + offset);
	}

	void show();
	void hide();

	//! @returns which object is currently controlling this text float (if known)
	const QObject* source() const { return m_source; }

	//! Sets which object is currently controlling this text float
	void setSource(const QObject* source) { m_source = source; }

private:
	QLabel * m_textLabel;
	QTimer * m_showTimer;
	QTimer * m_hideTimer;

	//! Which object is currently controlling this text float
	const QObject* m_source = nullptr;
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_SIMPLE_TEXT_FLOAT_H
