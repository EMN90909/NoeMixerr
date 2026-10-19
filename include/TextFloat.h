// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TEXT_FLOAT_H
#define NoeMixerr_GUI_TEXT_FLOAT_H

#include <QWidget>

#include "noemixerr_export.h"

class QLabel;

namespace noemixerr::gui
{

class NoeMixerr_EXPORT TextFloat : public QWidget
{
	Q_OBJECT
public:
	TextFloat();
	~TextFloat() override = default;

	void setTitle(const QString & title);
	void setText(const QString & text);
	void setPixmap(const QPixmap & pixmap);

	void setVisibilityTimeOut(int msecs);

	static TextFloat * displayMessage(const QString & title,
						const QString & msg,
						const QPixmap & pixmap = QPixmap(),
						int timeout = 2000,
						QWidget * parent = nullptr);

	void moveGlobal(QWidget * w, const QPoint & offset)
	{
		move(w->mapToGlobal(QPoint(0, 0)) + offset);
	}


protected:
	void mousePressEvent(QMouseEvent * me) override;


private:
	TextFloat(const QString & title, const QString & text, const QPixmap & pixmap);

	QLabel * m_pixmapLabel;
	QLabel * m_titleLabel;
	QLabel * m_textLabel;

};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TEXT_FLOAT_H
