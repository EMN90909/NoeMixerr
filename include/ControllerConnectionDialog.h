// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008  Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_CONTROLLER_CONNECTION_DIALOG_H
#define NoeMixerr_GUI_CONTROLLER_CONNECTION_DIALOG_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>

#include "Controller.h"
#include "AutomatableModel.h"


class QLineEdit;
class QListView;
class QScrollArea;

namespace noemixerr
{

class AutoDetectMidiController;

namespace gui
{

class ComboBox;
class GroupBox;
class TabWidget;
class LcdSpinBox;
class LedCheckBox;
class MidiPortMenu;


class ControllerConnectionDialog : public QDialog
{
	Q_OBJECT
public:
	ControllerConnectionDialog( QWidget * _parent,
			const AutomatableModel * _target_model );
	~ControllerConnectionDialog() override;

	Controller * chosenController()
	{
		return m_controller;
	}

public slots:
//	void setSelection( const effectKey & _selection );
	void selectController();
	void midiToggled();
	void userToggled();
	void userSelected();
	void autoDetectToggled();
	void enableAutoDetect( QAction * _a );


protected slots:
	void midiValueChanged();


private:
	// Midi
	GroupBox * m_midiGroupBox;
	LcdSpinBox * m_midiChannelSpinBox;
	LcdSpinBox * m_midiControllerSpinBox;
	LedCheckBox * m_midiAutoDetectCheckBox;
	MidiPortMenu * m_readablePorts;
	BoolModel m_midiAutoDetect;

	// User
	GroupBox * m_userGroupBox;
	ComboBox * m_userController;

	// Mapping
	TabWidget * m_mappingBox;
	QLineEdit * m_mappingFunction;

	Controller * m_controller;
	const AutomatableModel * m_targetModel;

	// Temporary midiController
	AutoDetectMidiController * m_midiController;
} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_CONTROLLER_CONNECTION_DIALOG_H
