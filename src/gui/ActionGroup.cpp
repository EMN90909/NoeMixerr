// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Lukas W <lukaswhl/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "ActionGroup.h"

namespace noemixerr::gui
{

ActionGroup::ActionGroup(QObject* parent) : QActionGroup(parent)
{
	connect(this, SIGNAL(triggered(QAction*)), this, SLOT(actionTriggered_(QAction*)));
}

QAction* ActionGroup::addAction(QAction* a)
{
	a->setCheckable(true);

	return QActionGroup::addAction(a);
}

QAction* ActionGroup::addAction(const QString& text)
{
	return addAction(new QAction(text, this));
}

QAction* ActionGroup::addAction(const QIcon& icon, const QString& text)
{
	return addAction(new QAction(icon, text, this));
}

void ActionGroup::actionTriggered_(QAction* action)
{
	Q_ASSERT(action != 0);
	Q_ASSERT(actions().contains(action));

	emit triggered(actions().indexOf(action));
}

} // namespace noemixerr::gui