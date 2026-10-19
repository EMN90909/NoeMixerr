// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Lukas W <lukaswhl/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_VERSIONED_SAVE_DIALOG_H
#define NoeMixerr_GUI_VERSIONED_SAVE_DIALOG_H

#include "FileDialog.h"
#include "Song.h"

class QLineEdit;

namespace noemixerr::gui
{

class LedCheckBox;

class SaveOptionsWidget : public QWidget {
public:
	SaveOptionsWidget(Song::SaveOptions &saveOptions);

private:
	LedCheckBox *m_discardMIDIConnectionsCheckbox;
	LedCheckBox *m_saveAsProjectBundleCheckbox;
};

class VersionedSaveDialog : public FileDialog
{
	Q_OBJECT
public:
	explicit VersionedSaveDialog( QWidget *parent = 0,
								  QWidget *saveOptionsWidget = nullptr,
								  const QString &caption = QString(),
								  const QString &directory = QString(),
								  const QString &filter = QString() );

	// Returns true if file name was changed, returns false if it wasn't
	static bool changeFileNameVersion( QString &fileName, bool increment );
	static bool fileExistsQuery( QString FileName, QString WindowTitle );

public slots:
	void incrementVersion();
	void decrementVersion();
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_VERSIONED_SAVE_DIALOG_H
