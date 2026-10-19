// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2007-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_EFFECT_VIEW_H
#define NoeMixerr_GUI_EFFECT_VIEW_H

#include "AutomatableModel.h"
#include "PluginView.h"
#include "Effect.h"

class QGraphicsOpacityEffect;
class QGroupBox;
class QLabel;
class QPushButton;
class QMdiSubWindow;

namespace noemixerr::gui
{

class EffectControlDialog;
class Knob;
class LedCheckBox;
class TempoSyncKnob;


class EffectView : public PluginView
{
	Q_OBJECT
public:
	EffectView( Effect * _model, QWidget * _parent );
	~EffectView() override;

	inline Effect * effect()
	{
		return castModel<Effect>();
	}
	inline const Effect * effect() const
	{
		return castModel<Effect>();
	}

	static constexpr int DEFAULT_WIDTH = 215;
	static constexpr int DEFAULT_HEIGHT = 60;
	
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
	void editControls();
	void moveUp();
	void moveDown();
	void deletePlugin();
	void corruptStateUpdate();

signals:
	void movedUp(EffectView* view);
	void movedDown(EffectView* view);
	void deletedPlugin(EffectView* view);

protected:
	void contextMenuEvent( QContextMenuEvent * _me ) override;
	void paintEvent( QPaintEvent * _pe ) override;
	void modelChanged() override;


private:
	QPixmap m_bg;
	LedCheckBox * m_bypass;
	Knob * m_wetDry;
	TempoSyncKnob * m_autoQuit;
	QMdiSubWindow * m_subWindow;
	EffectControlDialog * m_controlView;
	
	bool m_dragging;
	QGraphicsOpacityEffect* m_opacityEffect;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_EFFECT_VIEW_H
