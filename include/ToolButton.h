// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2006 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TOOL_BUTTON_H
#define NoeMixerr_GUI_TOOL_BUTTON_H

#include <QToolButton>

namespace noemixerr::gui
{

class ToolButton : public QToolButton
{
	Q_OBJECT
public:
	ToolButton(const QPixmap & _pixmap, const QString & _tooltip,
			QObject * _receiver=nullptr, const char * _slot=nullptr,
			QWidget * _parent=nullptr);

	inline ToolButton(QWidget * _parent) :
		QToolButton(_parent)
	{ }

	~ToolButton() override = default;

} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TOOL_BUTTON_H
