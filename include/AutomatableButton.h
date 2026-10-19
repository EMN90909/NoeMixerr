// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_AUTOMATABLE_BUTTON_H
#define NoeMixerr_GUI_AUTOMATABLE_BUTTON_H

#include <QPushButton>

#include "AutomatableModelView.h"

namespace noemixerr::gui
{

class AutomatableButtonGroup;


class NOEMIXERR_EXPORT AutomatableButton : public QPushButton, public BoolModelView
{
	Q_OBJECT
public:
	AutomatableButton( QWidget * _parent, const QString & _name
			= QString() );
	~AutomatableButton() override;

	inline void setCheckable( bool _on )
	{
		QPushButton::setCheckable( _on );
		model()->setJournalling( _on );
	}

	void modelChanged() override;


public slots:
	virtual void update();
	virtual void toggle();
	virtual void setChecked( bool _on )
	{
		// QPushButton::setChecked is called in update-slot
		model()->setValue( _on );
	}


protected:
	void contextMenuEvent( QContextMenuEvent * _me ) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void mouseReleaseEvent( QMouseEvent * _me ) override;


private:
	AutomatableButtonGroup * m_group;


	friend class AutomatableButtonGroup;

	using QPushButton::setChecked;
	using QPushButton::isChecked;
} ;



class NOEMIXERR_EXPORT AutomatableButtonGroup : public QWidget, public IntModelView
{
	Q_OBJECT
public:
	AutomatableButtonGroup( QWidget * _parent, const QString & _name
			= QString() );
	~AutomatableButtonGroup() override;

	void addButton( AutomatableButton * _btn );
	void removeButton( AutomatableButton * _btn );

	void activateButton( AutomatableButton * _btn );

	void modelChanged() override;


private slots:
	void updateButtons();


private:
	QList<AutomatableButton *> m_buttons;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_AUTOMATABLE_BUTTON_H
