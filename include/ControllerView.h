// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_CONTROLLER_VIEW_H
#define NoeMixerr_GUI_CONTROLLER_VIEW_H

#include <QFrame>

#include "AutomatableModel.h"
#include "Controller.h"
#include "ModelView.h"

class QGroupBox;
class QLabel;
class QPushButton;
class QMdiSubWindow;

namespace noemixerr::gui
{


class LedCheckBox;


class ControllerView : public QFrame, public ModelView
{
	Q_OBJECT
public:
	ControllerView( Controller * _controller, QWidget * _parent );
	~ControllerView() override;

	inline Controller * getController()
	{
		return( castModel<Controller>() );
	}

	inline const Controller * getController() const
	{
		return( castModel<Controller>() );
	}


public slots:
	void editControls();
	void removeController();
	void renameController();
	void moveUp();
	void moveDown();

signals:
	void movedUp(ControllerView* view);
	void movedDown(ControllerView* view);
	void removedController(ControllerView* view);


protected:
	void contextMenuEvent( QContextMenuEvent * _me ) override;
	void modelChanged() override;
	void mouseDoubleClickEvent( QMouseEvent * event ) override;


private:
	QMdiSubWindow * m_subWindow;
	ControllerDialog * m_controllerDlg;
	QLabel * m_nameLabel;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_CONTROLLER_VIEW_H
