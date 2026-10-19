// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Lukas W <lukaswhl/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Editor.h"

#include <QAction>
#include <QShortcut>

#include "DeprecationHelper.h"
#include "GuiApplication.h"
#include "MainWindow.h"
#include "Song.h"
#include "embed.h"

namespace noemixerr::gui
{


void Editor::setPauseIcon(bool displayPauseIcon)
{
	// If we're playing, show a pause icon
	if (displayPauseIcon)
		m_playAction->setIcon(embed::getIconPixmap("pause"));
	else
		m_playAction->setIcon(embed::getIconPixmap("play"));
}

DropToolBar * Editor::addDropToolBarToTop(QString const & windowTitle)
{
	return addDropToolBar(Qt::TopToolBarArea, windowTitle);
}

DropToolBar * Editor::addDropToolBar(Qt::ToolBarArea whereToAdd, QString const & windowTitle)
{
	return addDropToolBar(this, whereToAdd, windowTitle);
}

DropToolBar * Editor::addDropToolBar(QWidget * parent, Qt::ToolBarArea whereToAdd, QString const & windowTitle)
{
	auto toolBar = new DropToolBar(parent);
	addToolBar(whereToAdd, toolBar);
	toolBar->setMovable(false);
	toolBar->setFloatable(false);
	toolBar->setContextMenuPolicy(Qt::PreventContextMenu);
	toolBar->setWindowTitle(windowTitle);

	return toolBar;
}

void Editor::togglePlayStop()
{
	s_lastPlayedEditor = this;
	if (Engine::getSong()->isPlaying())
		stop();
	else
		play();
}

void Editor::togglePause()
{
	s_lastPlayedEditor = this;
	Engine::getSong()->togglePause();
}

void Editor::toggleMaximize()
{
	isMaximized() ? showNormal() : showMaximized();
}

Editor::Editor(bool record, bool stepRecord) :
	QMainWindow(),
	m_toolBar(new DropToolBar(this)),
	m_playAction(nullptr),
	m_recordAction(nullptr),
	m_recordAccompanyAction(nullptr),
	m_toggleStepRecordingAction(nullptr),
	m_stopAction(nullptr)
{
	m_toolBar = addDropToolBarToTop(tr("Transport controls"));

	auto addButton = [this](QAction* action, QString objectName) {
		m_toolBar->addAction(action);
		m_toolBar->widgetForAction(action)->setObjectName(objectName);
	};

	// Set up play and record actions
	m_playAction = new QAction(embed::getIconPixmap("play"), tr("Play (Space)"), this);
	m_stopAction = new QAction(embed::getIconPixmap("stop"), tr("Stop (Space)"), this);

	m_recordAction = new QAction(embed::getIconPixmap("record"), tr("Record"), this);
	m_recordAccompanyAction = new QAction(embed::getIconPixmap("record_accompany"), tr("Record while playing"), this);
	m_toggleStepRecordingAction = new QAction(embed::getIconPixmap("record_step_off"), tr("Toggle Step Recording"), this);

	// Set up connections
	connect(m_playAction, SIGNAL(triggered()), this, SLOT(play()));
	connect(m_recordAction, SIGNAL(triggered()), this, SLOT(record()));
	connect(m_recordAccompanyAction, SIGNAL(triggered()), this, SLOT(recordAccompany()));
	connect(m_toggleStepRecordingAction, SIGNAL(triggered()), this, SLOT(toggleStepRecording()));
	connect(m_stopAction, SIGNAL(triggered()), this, SLOT(stop()));
	new QShortcut(keySequence(Qt::SHIFT, Qt::Key_F11), this, SLOT(toggleMaximize()));

	// Add actions to toolbar
	addButton(m_playAction, "playButton");
	if (record)
	{
		addButton(m_recordAction, "recordButton");
		addButton(m_recordAccompanyAction, "recordAccompanyButton");
	}
	if(stepRecord)
	{
		addButton(m_toggleStepRecordingAction, "stepRecordButton");
	}
	addButton(m_stopAction, "stopButton");
}

QAction *Editor::playAction() const
{
	return m_playAction;
}

void Editor::keyPressEvent(QKeyEvent* ke)
{
	if (ke->key() == Qt::Key_Space)
	{
		if (ke->modifiers() & Qt::ShiftModifier)
		{
			togglePause();
		}
		else
		{
			togglePlayStop();
		}
		return;
	}
	ke->ignore();
}

DropToolBar::DropToolBar(QWidget* parent) : QToolBar(parent)
{
	setAcceptDrops(true);
}

void DropToolBar::dragEnterEvent(QDragEnterEvent* event)
{
	dragEntered(event);
}

void DropToolBar::dropEvent(QDropEvent* event)
{
	dropped(event);
}



} // namespace noemixerr::gui
