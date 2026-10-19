// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SIDE_BAR_WIDGET_H
#define NoeMixerr_GUI_SIDE_BAR_WIDGET_H

#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>

class QPushButton;

namespace noemixerr::gui
{


class SideBarWidget : public QWidget
{
	Q_OBJECT
public:
	SideBarWidget( const QString & _title, const QPixmap & _icon,
							QWidget * _parent );
	~SideBarWidget() override = default;

	inline const QPixmap & icon() const
	{
		return m_icon;
	}
	inline const QString & title() const
	{
		return m_title;
	}

signals:
	void closeButtonClicked();

protected:
	void paintEvent( QPaintEvent * _pe ) override;
	void resizeEvent( QResizeEvent * _re ) override;
	void contextMenuEvent( QContextMenuEvent * ) override
	{
	}

	QWidget * contentParent()
	{
		return m_contents;
	}

	void addContentWidget( QWidget * _w )
	{
		m_layout->addWidget( _w );
	}

	void addContentLayout( QLayout * _l )
	{
		m_layout->addLayout( _l );
	}

private:
	QWidget * m_contents;
	QVBoxLayout * m_layout;
	QString m_title;
	QPixmap m_icon;
	QPushButton * m_closeBtn;
	const QSize m_buttonSize;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_SIDE_BAR_WIDGET_H
