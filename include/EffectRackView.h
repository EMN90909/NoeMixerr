// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Danny McRae <khjklujn@netscape.net>
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_EFFECT_RACK_VIEW_H
#define NoeMixerr_GUI_EFFECT_RACK_VIEW_H

#include <QWidget>

#include "EffectChain.h"
#include "ModelView.h"

class QScrollArea;

namespace noemixerr::gui
{

class EffectView;
class GroupBox;


class EffectRackView : public QWidget, public ModelView
{
	Q_OBJECT
public:
	EffectRackView( EffectChain* model, QWidget* parent = nullptr );
	~EffectRackView() override;

	static constexpr int DEFAULT_WIDTH = 245;

public slots:
	void clearViews();
	void moveUp(EffectView* view);
	void moveDown(EffectView* view);
	void deletePlugin(EffectView* view);

private slots:
	virtual void update();
	void addEffect();


private:
	void modelChanged() override;
	QSize sizeHint() const override;
	QSize minimumSizeHint() const override { return sizeHint(); }

	inline EffectChain* fxChain()
	{
		return castModel<EffectChain>();
	}

	inline const EffectChain* fxChain() const
	{
		return castModel<EffectChain>();
	}


	QVector<EffectView *> m_effectViews;

	GroupBox* m_effectsGroupBox;
	QScrollArea* m_scrollArea;

	int m_lastY;

} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_EFFECT_RACK_VIEW_H
