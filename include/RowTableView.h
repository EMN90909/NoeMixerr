// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2016 Javier Serrano Polo <javier@jasp.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_ROW_TABLE_VIEW_H
#define NoeMixerr_GUI_ROW_TABLE_VIEW_H

#include <QTableView>

namespace noemixerr::gui
{


class RowDelegate;


class RowTableView : public QTableView
{
	Q_OBJECT
public:
	RowTableView( QWidget * parent = 0 );
	~RowTableView() override;

	void setModel( QAbstractItemModel * model ) override;


protected:
	void keyPressEvent( QKeyEvent * event ) override;


private:
	RowDelegate * m_rowDelegate;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_ROW_TABLE_VIEW_H
