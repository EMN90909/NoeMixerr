// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2005 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_RENAME_DIALOG_H
#define NoeMixerr_GUI_RENAME_DIALOG_H

#include <QDialog>

class QLineEdit;

namespace noemixerr::gui
{

class RenameDialog : public QDialog
{
	Q_OBJECT
public:
	RenameDialog( QString & _string );
	~RenameDialog() override = default;


protected:
	void keyPressEvent( QKeyEvent * _ke ) override;
	void resizeEvent(QResizeEvent * event) override;


protected slots:
	void textChanged( const QString & _new_string );


private:
	QString & m_stringToEdit;
	QString m_originalString;
	QLineEdit * m_stringLE;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_RENAME_DIALOG_H
