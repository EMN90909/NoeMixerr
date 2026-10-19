// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "TabBar.h"
#include "TabButton.h"


namespace noemixerr::gui
{


TabBar::TabBar( QWidget * _parent, QBoxLayout::Direction _dir ) :
	QWidget( _parent ),
	m_layout( new QBoxLayout( _dir, this ) ),
	m_exclusive( false )
{
	m_layout->setContentsMargins(8, 8, 8, 8);
	m_layout->setSpacing( 0 );

	setLayout( m_layout );
}

TabButton * TabBar::addTab( QWidget * _w, const QString & _text, int _id,
				bool _add_stretch, bool _text_is_tooltip, bool fixWidgetToParentSize )
{
	// already tab with id?
	if( m_tabs.contains( _id ) )
	{
		// then remove it
		removeTab( _id );
	}
	QString caption = ( _text_is_tooltip ) ? QString( "" ) : _text;
	// create tab-button
	auto b = new TabButton(caption, _id, this);
	connect( b, SIGNAL(clicked(int)), this, SLOT(tabClicked(int)));
	b->setIconSize( QSize( 48, 48 ) );
	b->setFixedSize( 64, 64 );
	b->show();
	if( _text_is_tooltip )
	{
		b->setToolTip(_text);
	}

	// small workaround, because QBoxLayout::addWidget(...) doesn't
	// work properly, so we first have to remove all tabs from the
	// layout and them add them in the correct order
	QMap<int, QPair<TabButton *, QWidget *> >::iterator it;
	for( it = m_tabs.begin(); it != m_tabs.end(); ++it )
	{
		m_layout->removeWidget( it.value().first );
	}
	m_tabs.insert( _id, qMakePair( b, _w ) );
	for( it = m_tabs.begin(); it != m_tabs.end(); ++it )
	{
		m_layout->addWidget( it.value().first );
	}

	if( _add_stretch )
	{
		m_layout->addStretch();
	}

	if (fixWidgetToParentSize)
	{
		// we assume, parent-widget is a widget acting as widget-stack so all
		// widgets have the same size and only the one on the top is visible
		_w->setFixedSize( _w->parentWidget()->size() );
	}

	return( b );
}




void TabBar::removeTab( int _id )
{
	// find tab-button and delete it
	if( m_tabs.find( _id ) != m_tabs.end() )
	{
		delete m_tabs[_id].first;
		m_tabs.erase( m_tabs.find( _id ) );
	}
}




void TabBar::setActiveTab( int _id )
{
	setTabState( _id, true );
	hideAll( _id );
	if( allHidden() )
	{
		emit allWidgetsHidden();
	}
	else
	{
		emit widgetShown();
	}
}




int TabBar::activeTab()
{
	QMap<int, QPair<TabButton *, QWidget *> >::iterator it;
	for( it = m_tabs.begin(); it != m_tabs.end(); ++it )
	{
		if( tabState( it.key() ) == true )
		{
			return( it.key() );
		}
	}
	return( -1 );
}




bool TabBar::tabState( int _id )
{
	if( m_tabs.find( _id ) == m_tabs.end() )
	{
		return( false );
	}
	return( m_tabs[_id].first->isChecked() );
}




void TabBar::setTabState( int _id, bool _checked )
{
	if( m_tabs.find( _id ) != m_tabs.end() )
	{
		m_tabs[_id].first->setChecked( _checked );
	}
}




void TabBar::hideAll( int _exception )
{
	QMap<int, QPair<TabButton *, QWidget *> >::iterator it;
	for( it = m_tabs.begin(); it != m_tabs.end(); ++it )
	{
		if( it.key() != _exception )
		{
			setTabState( it.key(), false );
		}
		it.value().second->hide();
	}
	if( m_tabs.find( _exception ) != m_tabs.end() )
	{
		if( tabState( _exception ) )
		{
			m_tabs[_exception].second->show();
		}
		else
		{
			m_tabs[_exception].second->hide();
		}
	}
}




void TabBar::tabClicked( int _id )
{
	if( m_exclusive == true && activeTab() == -1 )
	{
		setActiveTab( _id );
	}
	else
	{
		bool all_hidden_before = allHidden();
		// disable tabbar-buttons except the one clicked
		hideAll( _id );
		bool now_hidden = allHidden();
		if( all_hidden_before == true && now_hidden == false )
		{
			emit widgetShown();
		}
		else if( all_hidden_before == false && now_hidden == true )
		{
			emit allWidgetsHidden();
		}
	}
}




bool TabBar::allHidden()
{
	QMap<int, QPair<TabButton *, QWidget *> >::iterator it;
	for( it = m_tabs.begin(); it != m_tabs.end(); ++it )
	{
		if( !it.value().second->isHidden() )
		{
			return( false );
		}
	}
	return( true );
}


} // namespace noemixerr::gui
