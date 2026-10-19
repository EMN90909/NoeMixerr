// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Danny McRae <khjklujn/at/yahoo/com>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "NineButtonSelector.h"

#include "CaptionMenu.h"
#include "PixmapButton.h"

namespace noemixerr::gui
{


NineButtonSelector::NineButtonSelector(const std::array<QPixmap, 18>& onOffIcons, int defaultButton, int x, int y, QWidget* parent) :
	QWidget{parent},
	IntModelView{new NineButtonSelectorModel{defaultButton, 0, 8, nullptr, QString{}, true}, this}
{
	setFixedSize(50, 50);
	move(x, y);

	for (int i = 0; i < 9; ++i)
	{
		m_buttons[i] = new PixmapButton(this);
		const int buttonX = 1 + (i % 3) * 17;
		const int buttonY = 1 + (i / 3) * 17;
		m_buttons[i]->move(buttonX, buttonY);
		m_buttons[i]->setActiveGraphic(onOffIcons[i * 2]);
		m_buttons[i]->setInactiveGraphic(onOffIcons[(i * 2) + 1]);
		m_buttons[i]->setChecked(false);
		connect(m_buttons[i], &PixmapButton::clicked, this, [=, this](){ buttonClicked(i); });
	}

	m_lastBtn = m_buttons[defaultButton];
	m_lastBtn->setChecked(true);
}

void NineButtonSelector::buttonClicked(int id)
{
	setSelected(id);
}

void NineButtonSelector::modelChanged()
{
	updateButton(model()->value());
}

void NineButtonSelector::setSelected(int newButton)
{
	model()->setValue(newButton);
	updateButton(newButton);
}

void NineButtonSelector::updateButton(int newButton)
{
	m_lastBtn->setChecked(false);
	m_lastBtn->update();

	m_lastBtn = m_buttons[newButton];
	m_lastBtn->setChecked(true);
	m_lastBtn->update();

	emit NineButtonSelection(newButton);
}

void NineButtonSelector::contextMenuEvent(QContextMenuEvent*)
{
	CaptionMenu contextMenu{windowTitle(), this};
	contextMenu.exec(QCursor::pos());
}


} // namespace noemixerr::gui
