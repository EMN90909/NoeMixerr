// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2012 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_EXPORT_PROJECT_DIALOG_H
#define NoeMixerr_GUI_EXPORT_PROJECT_DIALOG_H

#include <QDialog>

#include "RenderManager.h"

class QString;
class QLabel;
class QProgressBar;
class QCheckBox;
class QComboBox;
class QSpinBox;
class QFormLayout;
class QGroupBox;

namespace noemixerr::gui {

class ExportProjectDialog : public QDialog
{
public:
	enum class Mode
	{
		ExportProject,
		ExportTracks,
	};

	ExportProjectDialog(const QString& path, Mode mode, QWidget* parent = nullptr);

private:
	void accept() override;
	void reject() override;
	void onFileFormatChanged(int index);
	void onStartButtonClicked();
	void updateTitleBar(int prog);

	QLabel* m_fileFormatLabel = nullptr;
	QComboBox* m_fileFormatComboBox = nullptr;

	QLabel* m_sampleRateLabel = nullptr;
	QComboBox* m_sampleRateComboBox = nullptr;

	QLabel* m_bitRateLabel = nullptr;
	QComboBox* m_bitRateComboBox = nullptr;

	QLabel* m_bitDepthLabel = nullptr;
	QComboBox* m_bitDepthComboBox = nullptr;

	QLabel* m_stereoModeLabel = nullptr;
	QComboBox* m_stereoModeComboBox = nullptr;

	QLabel* m_compressionLevelLabel = nullptr;
	QComboBox* m_compressionLevelComboBox = nullptr;

	QGroupBox* m_fileFormatSettingsGroupBox = nullptr;
	QFormLayout* m_fileFormatSettingsLayout = nullptr;

	QCheckBox* m_exportAsLoopBox = nullptr;
	QCheckBox* m_exportBetweenLoopMarkersBox = nullptr;
	QLabel* m_loopRepeatLabel = nullptr;
	QSpinBox* m_loopRepeatBox = nullptr;
	QPushButton* m_startButton = nullptr;
	QPushButton* m_cancelButton = nullptr;
	QProgressBar* m_progressBar = nullptr;

	QString m_path;
	Mode m_mode;
	std::unique_ptr<RenderManager> m_renderManager;
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_EXPORT_PROJECT_DIALOG_H
