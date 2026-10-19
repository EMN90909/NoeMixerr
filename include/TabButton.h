// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2007 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TAB_BUTTON_H
#define NoeMixerr_GUI_TAB_BUTTON_H

#include <QPushButton>

namespace noemixerr::gui
{


class TabButton : public QPushButton
{
	Q_OBJECT
public:
	TabButton( const QString & _text, int _id, QWidget * _parent ) :
		QPushButton( _text, _parent ),
		m_id( _id )
	{
		setCheckable( true );
		connect( this, SIGNAL( clicked() ), this,
						SLOT( slotClicked() ) );
	}

	~TabButton() override = default;


signals:
	void clicked( int );


protected slots:
	void slotClicked()
	{
		emit clicked( m_id );
	}


private:
	int m_id;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TAB_BUTTON_H
