// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef PATCHES_DIALOG_H
#define PATCHES_DIALOG_H

#include "ui_PatchesDialog.h"
#include "LcdSpinBox.h"
#include "GigPlayer.h"

#include <QWidget>
#include <QLabel>

//----------------------------------------------------------------------------
// qsynthPresetForm -- UI wrapper form.

namespace noemixerr::gui
{


class PatchesDialog : public QDialog, private Ui::PatchesDialog
{
	Q_OBJECT

public:

	// Constructor.
	PatchesDialog(QWidget * pParent = 0, Qt::WindowFlags wflags = QFlag(0));

	// Destructor.
	~PatchesDialog() override = default;


	void setup( GigInstance * pSynth, int iChan, const QString & chanName,
			LcdSpinBoxModel * bankModel, LcdSpinBoxModel * progModel, QLabel * patchLabel );

public slots:

	void stabilizeForm();
	void bankChanged();
	void progChanged( QTreeWidgetItem * curr, QTreeWidgetItem * prev );

protected slots:

	void accept() override;
	void reject() override;

protected:

	void setBankProg( int iBank, int iProg );

	QTreeWidgetItem * findBankItem( int iBank );
	QTreeWidgetItem * findProgItem( int iProg );

	bool validateForm();

private:

	// Instance variables.
	GigInstance * m_pSynth;

	int m_iChan;
	int m_iBank;
	int m_iProg;

	int m_dirty;

	LcdSpinBoxModel * m_bankModel;
	LcdSpinBoxModel * m_progModel;
	QLabel * m_patchLabel;
};


} // namespace noemixerr::gui

#endif
