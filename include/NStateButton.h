// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_NSTATE_BUTTON_H
#define NoeMixerr_GUI_NSTATE_BUTTON_H

#include <QPixmap>
#include <QVector>
#include <QPair>

#include "ToolButton.h"

namespace noemixerr::gui
{


class NStateButton : public ToolButton
{
	Q_OBJECT
public:
	NStateButton( QWidget * _parent );
	~NStateButton() override;
	void addState( const QPixmap & _pixmap, const QString & _tooltip = "" );

	inline void setGeneralToolTip( const QString & _tooltip )
	{
		m_generalToolTip = _tooltip;
	}

	inline int state() const
	{
		return( m_curState );
	}


public slots:
	void changeState(int state);

signals:
	void changedState(int state);

protected:
	void mousePressEvent(QMouseEvent* me) override;

private:
	QVector<QPair<QPixmap, QString>> m_states;
	QString m_generalToolTip;

	int m_curState;
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_NSTATE_BUTTON_H
