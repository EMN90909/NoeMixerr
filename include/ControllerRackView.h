// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_CONTROLLER_RACK_VIEW_H
#define NoeMixerr_GUI_CONTROLLER_RACK_VIEW_H

#include <QWidget>

#include "SerializingObject.h"

class QPushButton;
class QScrollArea;
class QVBoxLayout;


namespace noemixerr
{

class Controller;

namespace gui
{

class ControllerView;

class ControllerRackView : public QWidget, public SerializingObject
{
	Q_OBJECT
public:
	ControllerRackView();
	~ControllerRackView() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;

	inline QString nodeName() const override
	{
		return "ControllerRackView";
	}


public slots:
	void deleteController(ControllerView* view);
	void moveUp(ControllerView* view);
	void moveDown(ControllerView* view);
	void addController(Controller* controller);
	void removeController(Controller* controller);

private slots:
	void addController();


private:
	QVector<ControllerView *> m_controllerViews;

	QScrollArea * m_scrollArea;
	QVBoxLayout * m_scrollAreaLayout;
	QPushButton * m_addButton;

	// Stores the index of where to insert the next ControllerView.
	// Needed so that the StretchItem always stays at the last position.
	int m_nextIndex;
} ;

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_CONTROLLER_RACK_VIEW_H
