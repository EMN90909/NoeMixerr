// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Danny McRae <khjklujn/at/yahoo.com>
// Copyright (c) 2009-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TEMPO_SYNC_KNOB_H
#define NoeMixerr_GUI_TEMPO_SYNC_KNOB_H

#include <QPixmap>
#include <QPointer>

#include "Knob.h"
#include "TempoSyncKnobModel.h"

namespace noemixerr::gui
{

class MeterDialog;

class NoeMixerr_EXPORT TempoSyncKnob : public Knob
{
	Q_OBJECT
public:
	TempoSyncKnob( KnobType knobNum, QWidget* parent = nullptr, const QString& name = QString() );

	/**
	 * @brief Construct a TempoSyncKnob with the given style and label text.
	 * 
	 * @param knobNum Style of the knob
	 * @param labelText Text for the label
	 * @param parent Parent widget
	 * @param labelRendering Determines if the label uses the widget font or a font with a fixed size of 12 pixels (LegacyFixedFontSize). The default is to use the widget font.
	 * @param name Object name of the widget
	 */
	TempoSyncKnob(KnobType knobNum, const QString& labelText, QWidget* parent = nullptr, LabelRendering labelRendering = LabelRendering::WidgetFont, const QString& name = QString());

	/**
	 * @brief Constructs a tempo sync knob with a label font in the pixel size.
	 * 
	 * @param knobNum Style of the knob
	 * @param labelText Text for the label
	 * @param labelPixelSize Pixel size for the label
	 * @param parent Parent widget
	 * @param name Object name of the widget
	 */
	TempoSyncKnob(KnobType knobNum, const QString& labelText, int labelPixelSize, QWidget* parent, const QString& name = QString());

	~TempoSyncKnob() override;

	const QString & syncDescription();
	void setSyncDescription( const QString & _new_description );

	const QPixmap & syncIcon();
	void setSyncIcon( const QPixmap & _new_pix );

	TempoSyncKnobModel * model()
	{
		return castModel<TempoSyncKnobModel>();
	}

	void modelChanged() override;


signals:
	void syncDescriptionChanged( const QString & _new_description );
	void syncIconChanged();


protected:
	void contextMenuEvent( QContextMenuEvent * _me ) override;


protected slots:
	void updateDescAndIcon();
	void showCustom();


private:
	QPixmap m_tempoSyncIcon;
	QString m_tempoSyncDescription;

	QPointer<MeterDialog> m_custom;

} ;



} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TEMPO_SYNC_KNOB_H
