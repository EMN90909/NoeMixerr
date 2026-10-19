// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2017 Alexandre Almeida <http://m374lx.users.sourceforge.net/>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TRACK_RENAME_LINE_EDIT_H
#define NoeMixerr_GUI_TRACK_RENAME_LINE_EDIT_H

#include <QLineEdit>

namespace noemixerr::gui
{

class TrackRenameLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	TrackRenameLineEdit( QWidget * parent );
	void show();
	
protected:
	void keyPressEvent( QKeyEvent * ke ) override;
	
private:
	QString m_oldName;
} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TRACK_RENAME_LINE_EDIT_H
