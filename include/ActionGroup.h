// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Lukas W <lukaswhl/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_ACTION_GROUP_H
#define NoeMixerr_GUI_ACTION_GROUP_H

#include <QActionGroup>

namespace noemixerr::gui
{

/// \brief Convenience subclass of QActionGroup
///
/// This class provides the same functionality as QActionGroup, but in addition
/// has the actionTriggered(int) signal.
/// It also sets every added action's checkable property to true.
class ActionGroup : public QActionGroup
{
	Q_OBJECT
public:
	ActionGroup(QObject* parent);

	QAction* addAction(QAction *a);
	QAction* addAction(const QString &text);
	QAction* addAction(const QIcon &icon, const QString &text);

signals:
	/// This signal is emitted when the action at the given index is triggered.
	void triggered(int index);

private slots:
	void actionTriggered_(QAction* action);

private:
	QList<QAction*> m_actions;
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_ACTION_GROUP_H
