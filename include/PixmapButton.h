// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_PIXMAP_BUTTON_H
#define NoeMixerr_GUI_PIXMAP_BUTTON_H

#include <QPixmap>

#include "AutomatableButton.h"

namespace noemixerr::gui
{


class NOEMIXERR_EXPORT PixmapButton : public AutomatableButton
{
	Q_OBJECT
public:
	PixmapButton( QWidget * _parent,
					const QString & _name = QString() );
	~PixmapButton() override = default;

	void setActiveGraphic( const QPixmap & _pm );
	void setInactiveGraphic( const QPixmap & _pm, bool _update = true );

	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;

signals:
	void doubleClicked();


protected:
	void paintEvent( QPaintEvent * _pe ) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void mouseReleaseEvent( QMouseEvent * _me ) override;
	void mouseDoubleClickEvent( QMouseEvent * _me ) override;

private:
	bool isActive() const;

private:
	QPixmap m_activePixmap;
	QPixmap m_inactivePixmap;
	bool	m_pressed;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_PIXMAP_BUTTON_H
