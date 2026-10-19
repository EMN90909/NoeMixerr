// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019-2019 Johannes Lorenz <j.git$$$lorenz-ho.me, $$$=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LINKED_MODEL_GROUP_VIEWS_H
#define NoeMixerr_GUI_LINKED_MODEL_GROUP_VIEWS_H

#include <cstddef>
#include <memory>
#include <QWidget>

namespace noemixerr
{


class LinkedModelGroup;
class LinkedModelGroups;


namespace gui
{

class Control;  // IWYU pragma: keep

/**
	@file LinkedModelGroupViews.h
	See Lv2ViewBase.h for example usage
*/


/**
	View for a representative processor

	Features:
	* Remove button for removable models
	* Simple handling of adding, removing and model changing

	@note Neither this class, nor any inheriting classes, shall inherit
		ModelView. The "view" in the name is just for consistency
		with LinkedModelGroupsView.
*/
class LinkedModelGroupView : public QWidget
{
public:
	//! @param parent The parent widget
	//! @param model The linked model group
	//! @param colNum numbers of columns for the controls (link LEDs not counted)
	LinkedModelGroupView(QWidget* parent, LinkedModelGroup* model, std::size_t colNum);

	~LinkedModelGroupView() override = default;

	//! Reconnect models if model changed
	void modelChanged(LinkedModelGroup* linkedModelGroup);

protected:
	//! Add a control to this widget
	//! @warning This widget will own this control, do not free it
	void addControl(Control* ctrl, const std::string &id,
					const std::string& display, bool removable);

	void removeControl(const QString &key);

	void removeFocusFromSearchBar();

private:
	class LinkedModelGroup* m_model;

	//! column number in surrounding grid in LinkedModelGroupsView
	std::size_t m_colNum;
	class ControlLayout* m_layout;
	std::map<std::string, std::unique_ptr<class Control>> m_widgets;
};


/**
	Container class for one LinkedModelGroupView

	@note It's intended this class does not inherit from ModelView.
		Inheriting classes need to do that, see e.g. Lv2Instrument.h
*/
class LinkedModelGroupsView
{
protected:
	~LinkedModelGroupsView() = default;

	//! Reconnect models if model changed; to be called by child virtuals
	void modelChanged(LinkedModelGroups* ctrlBase);

private:
	//! The base class must return the addressed group view,
	//! which has the same value as "this"
	virtual LinkedModelGroupView* getGroupView() = 0;
};


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_LINKED_MODEL_GROUP_VIEWS_H
