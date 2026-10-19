// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Danny McRae <khjklujn/at/yahoo/com>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_NINE_BUTTON_SELECTOR_H
#define NoeMixerr_GUI_NINE_BUTTON_SELECTOR_H

#include <array>
#include <QWidget>

#include "AutomatableModelView.h"

namespace noemixerr
{


namespace gui
{

class PixmapButton;


class NineButtonSelector : public QWidget, public IntModelView
{
	Q_OBJECT
public:
	NineButtonSelector(const std::array<QPixmap, 18>& onOffIcons, int defaultButton, int x, int y, QWidget* parent);
	~NineButtonSelector() override = default;

protected:
	void setSelected(int newButton);

public slots:
	void buttonClicked(int id);
	void contextMenuEvent(QContextMenuEvent*) override;

signals:
	void NineButtonSelection(int);

private:
	void modelChanged() override;
	void updateButton(int);

	std::array<PixmapButton*, 9> m_buttons;
	PixmapButton* m_lastBtn;
};


} // namespace gui

using NineButtonSelectorModel = IntModel;


} // namespace noemixerr

#endif // NoeMixerr_GUI_NINE_BUTTON_SELECTOR_H
