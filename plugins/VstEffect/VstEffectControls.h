// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2011 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _VST_EFFECT_CONTROLS_H
#define _VST_EFFECT_CONTROLS_H

#include "EffectControls.h"


#include <QObject>

class QGridLayout;
class QPaintEvent;
class QPushButton;
class QMdiSubWindow;
class QScrollArea;

namespace noemixerr
{


class VstEffect;

namespace gui
{
class ManageVSTEffectView;
class VstEffectControlDialog;
class VstPluginKnob;
}


class VstEffectControls : public EffectControls
{
	Q_OBJECT
public:
	VstEffectControls( VstEffect * _eff );
	~VstEffectControls() override;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "vsteffectcontrols";
	}

	int controlCount() override;

	gui::EffectControlDialog* createView() override;


protected slots:
	void updateMenu();
	void managePlugin();
	void openPreset();
	void savePreset();
	void rollPreset();
	void rolrPreset();
	void selPreset();
	void setParameter( noemixerr::Model * action );

protected:
	virtual void paintEvent( QPaintEvent * _pe );

private:
	VstEffect * m_effect;

	QPushButton * m_selPresetButton;

	QMdiSubWindow * m_subWindow;
	QScrollArea * m_scrollArea;
	std::vector<FloatModel*> knobFModel;
	int paramCount;

	QObject * ctrHandle;

	int lastPosInMenu;
//	QLabel * m_presetLabel;

	friend class gui::VstEffectControlDialog;
	friend class gui::ManageVSTEffectView;

	bool m_vstGuiVisible;
} ;


namespace gui
{


class ManageVSTEffectView : public QObject
{
	Q_OBJECT
public:
	ManageVSTEffectView( VstEffect * _eff, VstEffectControls * m_vi );
	~ManageVSTEffectView() override;


protected slots:
	void syncPlugin();
	void displayAutomatedOnly();
	void setParameter( noemixerr::Model * action );
	void closeWindow();

private:
//	static QPixmap * s_artwork;

	VstEffectControls * m_vi2;


	VstEffect * m_effect;


	QWidget *widget;
	QGridLayout * l;

	QPushButton * m_syncButton;
	QPushButton * m_displayAutomatedOnly;
	QPushButton * m_closeButton;
	std::vector<VstPluginKnob*> m_vstKnobs;
};


} // namespace gui

} // namespace noemixerr

#endif
