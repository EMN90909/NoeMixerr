// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QStyleOptionToolButton>
#include <QStylePainter>
#include <QToolButton>

#include "SideBar.h"
#include "SideBarWidget.h"

namespace noemixerr::gui
{


// internal helper class allowing to create QToolButtons with
// vertical orientation
class SideBarButton : public QToolButton
{
public:
	SideBarButton( Qt::Orientation _orientation, QWidget * _parent ) :
		QToolButton( _parent ),
		m_orientation( _orientation )
	{
	}

	~SideBarButton() override = default;

	Qt::Orientation orientation() const
	{
		return m_orientation;
	}

	QSize sizeHint() const override
	{
		QSize s = QToolButton::sizeHint();
		s.setWidth( s.width() + 8 );
		if( orientation() == Qt::Horizontal )
		{
			return s;
		}
		return QSize( s.height(), s.width() );
	}


protected:
	void paintEvent( QPaintEvent * ) override
	{
		QStylePainter p( this );
		QStyleOptionToolButton opt;
		initStyleOption( &opt );
		if( orientation() == Qt::Vertical )
		{
			const QSize s = sizeHint();
			p.rotate( 270 );
			p.translate( -s.height(), 0 );
			opt.rect = QRect( 0, 0, s.height(), s.width() );
		}
		p.drawComplexControl( QStyle::CC_ToolButton, opt );
	}


private:
	Qt::Orientation m_orientation;

} ;


SideBar::SideBar( Qt::Orientation _orientation, QWidget * _parent ) :
	QToolBar( _parent ),
	m_btnGroup( this )
{
	setOrientation( _orientation );
	setIconSize( QSize( 16, 16 ) );

	m_btnGroup.setExclusive( false );
	connect( &m_btnGroup, SIGNAL(buttonClicked(QAbstractButton*)),
				this, SLOT(toggleButton(QAbstractButton*)));
}




void SideBar::appendTab( SideBarWidget *widget )
{
	auto button = new SideBarButton(orientation(), this);
	button->setText( " " + widget->title() );
	button->setIcon( widget->icon() );
	button->setLayoutDirection( Qt::RightToLeft );
	button->setCheckable( true );
	m_widgets[button] = widget;
	m_btnGroup.addButton( button );
	addWidget( button );

	widget->hide();
	widget->setMinimumWidth( 200 );

	button->setToolTip(widget->title());

	connect(widget, &SideBarWidget::closeButtonClicked,
		[=]() { button->click(); });
}




void SideBar::toggleButton( QAbstractButton * button )
{
	QToolButton *toolButton = nullptr;
	QWidget *activeWidget = nullptr;

	for( auto it = m_widgets.begin(); it != m_widgets.end(); ++it )
	{
		QToolButton *curBtn = it.key();
		QWidget *curWidget = it.value();

		if( curBtn == button )
		{
			toolButton = curBtn;
			activeWidget = curWidget;
		}
		else
		{
			curBtn->setChecked( false );
			curBtn->setToolButtonStyle( Qt::ToolButtonIconOnly );
		}

		if( curWidget )
		{
			curWidget->hide();
		}
	}

	if( toolButton && activeWidget )
	{
		activeWidget->setVisible( button->isChecked() );
		toolButton->setToolButtonStyle( button->isChecked() ?
				Qt::ToolButtonTextBesideIcon : Qt::ToolButtonIconOnly );
	}
}


} // namespace noemixerr::gui
