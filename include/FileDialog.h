// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Lukas W <lukaswhl/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_FILE_DIALOG_H
#define NoeMixerr_GUI_FILE_DIALOG_H

#include <QFileDialog>

#include "noemixerr_export.h"

namespace noemixerr::gui
{


class NOEMIXERR_EXPORT FileDialog : public QFileDialog
{
	Q_OBJECT
public:
	explicit FileDialog( QWidget *parent = 0, const QString &caption = QString(),
						const QString &directory = QString(),
						const QString &filter = QString() );

	static QString getExistingDirectory(QWidget *parent,
										const QString &caption,
										const QString &directory,
										QFileDialog::Options options = QFileDialog::ShowDirsOnly);
    static QString getOpenFileName(QWidget *parent = 0,
									const QString &caption = QString(),
									const QString &directory = QString(),
									const QString &filter = QString(),
									QString *selectedFilter = 0);
	static QString openAudioFile(const QString& previousFile = "");
	static QString openWaveformFile(const QString& previousFile = "");
	void clearSelection();
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_FILE_DIALOG_H
