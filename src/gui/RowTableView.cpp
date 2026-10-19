// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2016 Javier Serrano Polo <javier@jasp.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "RowTableView.h"

#include <QKeyEvent>
#include <QPainter>
#include <QStyledItemDelegate>


namespace noemixerr::gui
{


class RowDelegate : public QStyledItemDelegate
{
public:
	RowDelegate( QAbstractItemView * table, QObject * parent = 0 ) :
		QStyledItemDelegate( parent ),
		m_table( table )
		{
		}
	void paint( QPainter * painter,
					const QStyleOptionViewItem & option,
					const QModelIndex & index ) const override;


protected:
	void initStyleOption( QStyleOptionViewItem * option,
					const QModelIndex & index ) const override;


private:
	QAbstractItemView * m_table;

} ;




void RowDelegate::initStyleOption( QStyleOptionViewItem * option,
					const QModelIndex & index ) const
{
	QStyledItemDelegate::initStyleOption( option, index );
	option->state &= ~QStyle::State_HasFocus;
}




void RowDelegate::paint( QPainter * painter,
	const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	QStyledItemDelegate::paint( painter, option, index );
	if ( index.row() == m_table->currentIndex().row() )
	{
		const QRect rect( option.rect );
		painter->drawLine( rect.topLeft(), rect.topRight() );
		painter->drawLine( rect.bottomLeft(), rect.bottomRight() );
		if ( index.column() == 0 )
		{
			painter->drawLine( rect.topLeft(), rect.bottomLeft() );
		}
		if ( index.column() == index.model()->columnCount() - 1 )
		{
			painter->drawLine( rect.topRight(),
							rect.bottomRight() );
		}
	}
}




RowTableView::RowTableView( QWidget * parent ) :
	QTableView( parent )
{
	m_rowDelegate = new RowDelegate( this, this );
}




RowTableView::~RowTableView()
{
	delete m_rowDelegate;
}




void RowTableView::setModel( QAbstractItemModel * model )
{
	QTableView::setModel( model );
	for ( int i = 0; i < model->rowCount(); i++ )
	{
		setItemDelegateForRow( i, m_rowDelegate );
	}

}




void RowTableView::keyPressEvent( QKeyEvent * event )
{
	switch( event->key() )
	{
		case Qt::Key_Tab:
		case Qt::Key_Backtab:
			for( int i = 0; i < model()->columnCount() - 1; i++ )
			{
				QTableView::keyPressEvent( event );
			}
		default:
			QTableView::keyPressEvent( event );
	}
}


} // namespace noemixerr::gui
