// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <QKeyEvent>
#include <QLineEdit>

#include "RenameDialog.h"

namespace noemixerr::gui
{


RenameDialog::RenameDialog( QString & _string ) :
	QDialog(),
	m_stringToEdit( _string ),
	m_originalString( _string )
{
	setWindowTitle( tr("Rename...") );
	setFixedHeight( 30 );
	m_stringLE = new QLineEdit( this );
	m_stringLE->setText( _string );
	m_stringLE->setGeometry ( 10, 5, 220, 20 );
	m_stringLE->selectAll();
	connect( m_stringLE, SIGNAL( textChanged( const QString& ) ), this,
				SLOT( textChanged( const QString& ) ) );
	connect( m_stringLE, SIGNAL(returnPressed()), this,
							SLOT(accept()));
}





void RenameDialog::resizeEvent (QResizeEvent * event) {
	m_stringLE->setGeometry ( 10, 5, width() - 20, 20 );	
}




void RenameDialog::keyPressEvent( QKeyEvent * _ke )
{
	if( _ke->key() == Qt::Key_Escape )
	{
		m_stringLE->setText( m_originalString );
		accept();
	}
}




void RenameDialog::textChanged( const QString & _new_string )
{
	m_stringToEdit = _new_string;
}


} // namespace noemixerr::gui