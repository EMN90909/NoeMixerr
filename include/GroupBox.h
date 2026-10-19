// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_GROUP_BOX_H
#define NoeMixerr_GUI_GROUP_BOX_H

#include <QWidget>

#include "AutomatableModelView.h"
#include "PixmapButton.h"


class QPixmap;

namespace noemixerr::gui
{

class GroupBox : public QWidget, public BoolModelView
{
	Q_OBJECT
public:
	GroupBox( const QString & _caption, QWidget * _parent = nullptr );
	~GroupBox() override;

	void modelChanged() override;

	PixmapButton * ledButton()
	{
		return m_led;
	}

	/**
	 * @brief Returns whether the LED button is shown or not
	 * 
	 * @return true LED button is shown
	 * @return false LED button is hidden
	 */
	bool ledButtonShown() const;

	/**
	 * @brief Sets if the LED check box is shown or not
	 * 
	 * @param value Set to true to show the LED check box or to false to hide it.
	 */
	void setLedButtonShown(bool value);

	int titleBarHeight() const
	{
		return m_titleBarHeight;
	}


protected:
	void mousePressEvent( QMouseEvent * _me ) override;
	void paintEvent( QPaintEvent * _pe ) override;


private:
	void updatePixmap();

	PixmapButton * m_led;
	QString m_caption;
	const int m_titleBarHeight;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_GROUP_BOX_H
