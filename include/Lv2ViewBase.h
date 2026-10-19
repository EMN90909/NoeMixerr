// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LV2_VIEW_BASE_H
#define NoeMixerr_GUI_LV2_VIEW_BASE_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_LV2


#include "LinkedModelGroupViews.h"
#include "noemixerr_export.h"
#include "Lv2Basics.h"


class QPushButton;
class QMdiSubWindow;
namespace noemixerr
{


class Lv2Proc;
class Lv2ControlBase;


namespace gui
{


//! View for one processor, Lv2ViewBase contains 2 of those for mono plugins
class Lv2ViewProc : public LinkedModelGroupView
{
public:
	//! @param colNum numbers of columns for the controls
	Lv2ViewProc(QWidget *parent, Lv2Proc *proc, int colNum);
	~Lv2ViewProc() override = default;

private:
	static AutoLilvNode uri(const char *uriStr);
};




class HelpWindowEventFilter : public QObject
{
	Q_OBJECT
	class Lv2ViewBase* const m_viewBase;
protected:
	bool eventFilter(QObject* obj, QEvent* event) override;
public:
	HelpWindowEventFilter(class Lv2ViewBase* viewBase);
};




//! Base class for view for one Lv2 plugin
class NOEMIXERR_EXPORT Lv2ViewBase : public LinkedModelGroupsView
{
	friend class HelpWindowEventFilter;
protected:
	//! @param pluginWidget A child class which inherits QWidget
	Lv2ViewBase(class QWidget *pluginWidget, Lv2ControlBase *ctrlBase);
	~Lv2ViewBase();

	// these widgets must be connected by child widgets
	QPushButton* m_reloadPluginButton = nullptr;
	QPushButton* m_toggleUIButton = nullptr;
	QPushButton* m_helpButton = nullptr;

	void toggleUI();
	void toggleHelp(bool visible);
	void closeHelpWindow();

	// to be called by child virtuals
	//! Reconnect models if model changed
	void modelChanged(Lv2ControlBase* ctrlBase);

private:
	enum Rows
	{
		ButtonRow,
		ProcRow,
		LinkChannelsRow
	};

	static AutoLilvNode uri(const char *uriStr);
	LinkedModelGroupView* getGroupView() override { return m_procView; }
	void onHelpWindowClosed();

	Lv2ViewProc* m_procView;

	//! Numbers of controls per row; must be multiple of 2 for mono effects
	const int m_colNum = 6;
	QMdiSubWindow* m_helpWindow = nullptr;
	HelpWindowEventFilter m_helpWindowEventFilter;
};


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

#endif // NoeMixerr_GUI_LV2_VIEW_BASE_H
