// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Danny McRae <khjklujn/at/yahoo.com>
// Copyright (c) 2009-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2023 Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TEMPO_SYNC_BAR_MODEL_EDITOR_H
#define NoeMixerr_GUI_TEMPO_SYNC_BAR_MODEL_EDITOR_H

#include <QPixmap>
#include <QPointer>

#include "BarModelEditor.h"
#include "TempoSyncKnobModel.h"

namespace noemixerr::gui
{

class MeterDialog;

class NOEMIXERR_EXPORT TempoSyncBarModelEditor : public BarModelEditor
{
	Q_OBJECT
public:
	TempoSyncBarModelEditor(QString text, FloatModel * floatModel, QWidget * parent = nullptr);
	~TempoSyncBarModelEditor() override;

	const QString & syncDescription();
	void setSyncDescription(const QString & new_description);

	const QPixmap & syncIcon();
	void setSyncIcon(const QPixmap & new_pix);

	TempoSyncKnobModel * model()
	{
		return castModel<TempoSyncKnobModel>();
	}

	void modelChanged() override;


signals:
	void syncDescriptionChanged(const QString & new_description);
	void syncIconChanged();


protected:
	void contextMenuEvent(QContextMenuEvent * me) override;


protected slots:
	void updateDescAndIcon();
	void showCustom();


private:
	void updateTextDescription();
	void updateIcon();


private:
	QPixmap m_tempoSyncIcon;
	QString m_tempoSyncDescription;

	QPointer<MeterDialog> m_custom;
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TEMPO_SYNC_BAR_MODEL_EDITOR_H
