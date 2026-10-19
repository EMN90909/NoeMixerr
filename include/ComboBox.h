// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_COMBOBOX_H
#define NoeMixerr_GUI_COMBOBOX_H

#include <QMenu>
#include <QWidget>

#include "ComboBoxModel.h"
#include "AutomatableModelView.h"

namespace noemixerr::gui
{

class NoeMixerr_EXPORT ComboBox : public QWidget, public IntModelView
{
	Q_OBJECT
public:
	ComboBox( QWidget* parent = nullptr, const QString& name = QString() );
	~ComboBox() override = default;

	ComboBoxModel* model()
	{
		return castModel<ComboBoxModel>();
	}

	const ComboBoxModel* model() const
	{
		return castModel<ComboBoxModel>();
	}

	static constexpr int DEFAULT_HEIGHT = 22;

public slots:
	void selectNext();
	void selectPrevious();


protected:
	void contextMenuEvent( QContextMenuEvent* event ) override;
	void mousePressEvent( QMouseEvent* event ) override;
	void paintEvent( QPaintEvent* event ) override;
	void wheelEvent( QWheelEvent* event ) override;


private:
	QPixmap m_background = embed::getIconPixmap("combobox_bg");
	QPixmap m_arrow = embed::getIconPixmap("combobox_arrow");
	QPixmap m_arrowSelected = embed::getIconPixmap("combobox_arrow_selected");

	QMenu m_menu;

	bool m_pressed;


private slots:
	void setItem( QAction* item );

} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_COMBOBOX_H
