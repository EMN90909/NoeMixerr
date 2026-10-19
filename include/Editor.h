// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Lukas W <lukaswhl/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_EDITOR_H
#define NoeMixerr_GUI_EDITOR_H

#include <QMainWindow>
#include <QToolBar>

class QAction;

namespace noemixerr::gui
{

static const int Quantizations[] = {
	1, 2, 4, 8, 16, 32, 64,
	3, 6, 12, 24, 48, 96, 192
};


class DropToolBar;

/// \brief Superclass for editors with a toolbar.
///
/// Those editors include the Song Editor, the Automation Editor, B&B Editor,
/// and the Piano Roll.
class Editor : public QMainWindow
{
	Q_OBJECT
public:
	void setPauseIcon(bool displayPauseIcon=true);
	QAction *playAction() const;
	static Editor* lastPlayedEditor() { return s_lastPlayedEditor; }
protected:
	DropToolBar * addDropToolBarToTop(QString const & windowTitle);
	DropToolBar * addDropToolBar(Qt::ToolBarArea whereToAdd, QString const & windowTitle);
	DropToolBar * addDropToolBar(QWidget * parent, Qt::ToolBarArea whereToAdd, QString const & windowTitle);

	void keyPressEvent(QKeyEvent* ke) override;

public slots:
	//! Called by pressing the space key. Plays or stops.
	void togglePlayStop();
	//! Called by pressing shift+space. Toggles pause state.
	void togglePause();

protected slots:
	virtual void play() {}
	virtual void record() {}
	virtual void recordAccompany() {}
	virtual void toggleStepRecording() {}
	virtual void stop() {}

private slots:
	void toggleMaximize();
private:
	inline static Editor* s_lastPlayedEditor = nullptr;

signals:

protected:
	//! @param record If set true, the editor's toolbar will contain
	//! record buttons in addition to the play and stop buttons.
	//! @param stepRecord If set true, the editor's toolbar will also
	//! contain a step record button.
	Editor(bool record = false, bool stepRecord = false);
	~Editor() override = default;


	DropToolBar* m_toolBar;

	QAction* m_playAction;
	QAction* m_recordAction;
	QAction* m_recordAccompanyAction;
	QAction* m_toggleStepRecordingAction;
	QAction* m_stopAction;
};


/// Small helper class: A QToolBar that accepts and exposes drop events as signals
class DropToolBar : public QToolBar
{
	Q_OBJECT
public:
	DropToolBar(QWidget* parent=0);

signals:
	void dragEntered(QDragEnterEvent* event);
	void dropped(QDropEvent* event);

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_EDITOR_H
