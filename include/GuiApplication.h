// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Lukas W <lukaswhl/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_GUI_APPLICATION_H
#define NoeMixerr_GUI_GUI_APPLICATION_H

#include <QObject>

#include "noemixerr_export.h"
#include "noemixerrconfig.h"

class QLabel;
class QSocketNotifier;

namespace noemixerr::gui
{

class AutomationEditorWindow;
class ControllerRackView;
class MixerView;
class MainWindow;
class MicrotunerConfig;
class PatternEditorWindow;
class PianoRollWindow;
class ProjectNotes;
class SongEditorWindow;

class NOEMIXERR_EXPORT GuiApplication : public QObject
{
	Q_OBJECT;
public:
	explicit GuiApplication();
	~GuiApplication() override;

	static GuiApplication* instance();

	//! @brief Called from main when SIGINT is fired
	//!
	//! Unix signal handlers can only call async-signal-safe functions:
	//! `write(fd)` -> `QSocketNotifier` -> `SLOT sigintOccurred()`
	//!
	//! @see https://doc.qt.io/qt-6/unix-signals.html
	static void sigintHandler(int);

	static bool isWayland();
#ifdef NoeMixerr_BUILD_WIN32
	//! @brief Returns the Windows System font.
	static QFont getWin32SystemFont();
#endif

	void createSocketNotifier();

	MainWindow* mainWindow() { return m_mainWindow; }
	MixerView* mixerView() { return m_mixerView; }
	SongEditorWindow* songEditor() { return m_songEditor; }
	PatternEditorWindow* patternEditor() { return m_patternEditor; }
	PianoRollWindow* pianoRoll() { return m_pianoRoll; }
	ProjectNotes* getProjectNotes() { return m_projectNotes; }
	MicrotunerConfig* getMicrotunerConfig() { return m_microtunerConfig; }
	AutomationEditorWindow* automationEditor() { return m_automationEditor; }
	ControllerRackView* getControllerRackView() { return m_controllerRackView; }

	//! File descriptors for unix socketpair, used to receive SIGINT
	static inline int s_sigintFd[2];

public slots:
	void displayInitProgress(const QString &msg);

private slots:
	void childDestroyed(QObject *obj);
	void sigintOccurred();

private:
	static GuiApplication* s_instance;

	MainWindow* m_mainWindow;
	MixerView* m_mixerView;
	SongEditorWindow* m_songEditor;
	AutomationEditorWindow* m_automationEditor;
	PatternEditorWindow* m_patternEditor;
	PianoRollWindow* m_pianoRoll;
	ProjectNotes* m_projectNotes;
	MicrotunerConfig* m_microtunerConfig;
	ControllerRackView* m_controllerRackView;
	QLabel* m_loadingProgressLabel;
	QSocketNotifier* m_sigintNotifier;
};

// Short-hand function
NOEMIXERR_EXPORT GuiApplication* getGUI();

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_GUI_APPLICATION_H
