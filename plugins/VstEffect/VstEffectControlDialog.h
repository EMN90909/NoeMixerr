// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _VST_EFFECT_CONTROL_DIALOG_H
#define _VST_EFFECT_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

#include <QSharedPointer>

class QPushButton;
class QLabel;

namespace noemixerr
{

class VstEffectControls;
class VstPlugin;

namespace gui
{

class PixmapButton;


class VstEffectControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	VstEffectControlDialog( VstEffectControls * _controls );
	~VstEffectControlDialog() override;

protected:
	void paintEvent( QPaintEvent * _pe ) override;
	void showEvent( QShowEvent* _se ) override;

private:
	QWidget * m_pluginWidget;

	QPushButton * m_togglePluginButton;
	PixmapButton * m_openPresetButton;
	QPushButton* m_rolLPresetButton;
	QPushButton* m_rolRPresetButton;
	PixmapButton * m_managePluginButton;
	PixmapButton * m_savePresetButton;

	QSharedPointer<VstPlugin> m_plugin;

	QLabel * tbLabel;

public slots:
	void togglePluginUI( bool checked );
} ;


} // namespace gui

} // namespace noemixerr

#endif
