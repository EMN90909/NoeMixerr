// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SETUP_DIALOG_H
#define NoeMixerr_GUI_SETUP_DIALOG_H

#include <QDialog>
#include <QMap>

#include "AudioDevice.h"
#include "AudioDeviceSetupWidget.h"
#include "MidiClient.h"
#include "MidiSetupWidget.h"


class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QSlider;


namespace noemixerr::gui
{


class TabBar;

class SetupDialog : public QDialog
{
	Q_OBJECT

public:
	enum class ConfigTab
	{
		GeneralSettings,
		PerformanceSettings,
		AudioSettings,
		MidiSettings,
		PathsSettings
	};

	SetupDialog(ConfigTab tab_to_open = ConfigTab::GeneralSettings);
	~SetupDialog() override;


protected slots:
	void accept() override;


private slots:
	// General settings widget.
	void toggleTooltips(bool enabled);
	void toggleDisplayWaveform(bool enabled);
	void toggleNoteLabels(bool enabled);
	void toggleShowFaderTicks(bool enabled);
	void toggleCompactTrackButtons(bool enabled);
	void toggleOneInstrumentTrackWindow(bool enabled);
	void toggleSideBarOnRight(bool enabled);
	void toggleLetPreviewsFinish(bool enabled);
	void toggleSoloLegacyBehavior(bool enabled);
	void toggleTrackDeletionWarning(bool enabled);
	void toggleMixerChannelDeletionWarning(bool enabled);
	void toggleMMPZ(bool enabled);
	void toggleDisableBackup(bool enabled);
	void toggleOpenLastProject(bool enabled);
	void detachBehaviorChanged();
	void loopMarkerModeChanged();
	void setLanguage(int lang);

	// Performance settings widget.
	void setAutoSaveInterval(int time);
	void resetAutoSave();
	void toggleAutoSave(bool enabled);
	void toggleRunningAutoSave(bool enabled);
	void toggleSmoothScroll(bool enabled);
	void toggleAnimateAFP(bool enabled);
	void vstEmbedMethodChanged();
	void toggleVSTAlwaysOnTop(bool en);
	void toggleDisableAutoQuit(bool enabled);
	void toggleMixSanitization(bool enabled);

	// Audio settings widget.
	void audioInterfaceChanged(const QString & driver);
	void updateBufferSizeWarning(int value);
	void setBufferSize(int value);
	void resetBufferSize();

	// MIDI settings widget.
	void midiInterfaceChanged(const QString & driver);
	void toggleMidiAutoQuantization(bool enabled);

	// Paths settings widget.
	void openWorkingDir();
	void setWorkingDir(const QString & workingDir);
	void openVSTDir();
	void setVSTDir(const QString & vstDir);
	void openLADSPADir();
	void setLADSPADir(const QString & ladspaDir);
	void openSF2Dir();
	void setSF2Dir(const QString & sf2Dir);
	void openSF2File();
	void setSF2File(const QString & sf2File);
	void openGIGDir();
	void setGIGDir(const QString & gigDir);
	void openThemeDir();
	void setThemeDir(const QString & themeDir);
	void openBackgroundPicFile();
	void setBackgroundPicFile(const QString & backgroundPicFile);

	void showRestartWarning();

private:
	TabBar * m_tabBar;

	// General settings widgets.
	bool m_tooltips;
	bool m_displayWaveform;
	bool m_printNoteLabels;
	bool m_showFaderTicks;
	bool m_compactTrackButtons;
	bool m_oneInstrumentTrackWindow;
	bool m_sideBarOnRight;
	bool m_letPreviewsFinish;
	bool m_soloLegacyBehavior;
	bool m_trackDeletionWarning;
	bool m_mixerChannelDeletionWarning;
	bool m_MMPZ;
	bool m_disableBackup;
	bool m_openLastProject;
	QString m_detachBehavior;
	QComboBox* m_detachBehaviorComboBox;
	QString m_loopMarkerMode;
	QComboBox* m_loopMarkerComboBox;
	QString m_autoScroll;
	QComboBox* m_autoScrollComboBox;
	QString m_lang;
	QStringList m_languages;

	// Performance settings widgets.
	int m_saveInterval;
	bool m_enableAutoSave;
	bool m_enableRunningAutoSave;
	QSlider * m_saveIntervalSlider;
	QLabel * m_saveIntervalLbl;
	QCheckBox * m_autoSave;
	QCheckBox * m_runningAutoSave;
	bool m_smoothScroll;
	bool m_animateAFP;
	QLabel * m_vstEmbedLbl;
	QComboBox* m_vstEmbedComboBox;
	QString m_vstEmbedMethod;
	QCheckBox * m_vstAlwaysOnTopCheckBox;
	bool m_vstAlwaysOnTop;
	bool m_disableAutoQuit;

	using AswMap = QMap<QString, AudioDeviceSetupWidget*>;
	using MswMap = QMap<QString, MidiSetupWidget*>;
	using trMap = QMap<QString, QString>;

	// Audio settings widgets.
	QComboBox * m_audioInterfaces;
	AswMap m_audioIfaceSetupWidgets;
	trMap m_audioIfaceNames;
	int m_bufferSize;
	QSlider * m_bufferSizeSlider;
	QLabel * m_bufferSizeLbl;
	QLabel * m_bufferSizeWarnLbl;
	bool m_mixSanitization;
	int m_sampleRate;
	QSlider* m_sampleRateSlider;

	// MIDI settings widgets.
	QComboBox * m_midiInterfaces;
	MswMap m_midiIfaceSetupWidgets;
	trMap m_midiIfaceNames;
	QComboBox * m_assignableMidiDevices;
	bool m_midiAutoQuantize;

	// Paths settings widgets.
	QString m_workingDir;
	QString m_vstDir;
	QString m_ladspaDir;
	QString m_gigDir;
	QString m_sf2Dir;
#ifdef NoeMixerr_HAVE_FLUIDSYNTH
	QString m_sf2File;
#endif
	QString m_themeDir;
	QString m_backgroundPicFile;

	QLineEdit * m_workingDirLineEdit;
	QLineEdit * m_vstDirLineEdit;
	QLineEdit * m_themeDirLineEdit;
	QLineEdit * m_ladspaDirLineEdit;
	QLineEdit * m_gigDirLineEdit;
	QLineEdit * m_sf2DirLineEdit;
#ifdef NoeMixerr_HAVE_FLUIDSYNTH
	QLineEdit * m_sf2FileLineEdit;
#endif
	QLineEdit * m_backgroundPicFileLineEdit;

	QLabel * restartWarningLbl;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_SETUP_DIALOG_H
