// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2015 Colin Wallace <wallacoloo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <QHBoxLayout>

#include "LeftRightNav.h"
#include "embed.h"

namespace noemixerr::gui
{


LeftRightNav::LeftRightNav(QWidget *parent)
	: QWidget(parent)
	, m_layout(this)
	, m_leftBtn(this)
	, m_rightBtn(this)
{
	m_layout.setContentsMargins(0, 0, 0, 0);
	m_layout.setSpacing(2);

	m_leftBtn.setObjectName("btn-stepper-left");
	m_rightBtn.setObjectName("btn-stepper-right");

	m_leftBtn.setCheckable(false);
	m_rightBtn.setCheckable(false);

	m_leftBtn.setCursor(Qt::PointingHandCursor);
	m_rightBtn.setCursor(Qt::PointingHandCursor);

	connect(&m_leftBtn, SIGNAL(clicked()), this,
						SIGNAL(onNavLeft()));
	connect(&m_rightBtn, SIGNAL(clicked()), this,
						SIGNAL(onNavRight()));

	m_leftBtn.setToolTip(tr("Previous"));
	m_rightBtn.setToolTip(tr("Next"));

	// The context menu contains irrelevant options for these buttons,
	// such as copying and pasting values
	m_leftBtn.setContextMenuPolicy(Qt::NoContextMenu);
	m_rightBtn.setContextMenuPolicy(Qt::NoContextMenu);

	m_layout.addWidget(&m_leftBtn);
	m_layout.addWidget(&m_rightBtn);
}


void LeftRightNav::setShortcuts(const QKeySequence &leftShortcut, const QKeySequence &rightShortcut)
{
	m_leftBtn.setShortcut(leftShortcut);
	m_rightBtn.setShortcut(rightShortcut);

	m_leftBtn.setToolTip(tr("Previous (%1)").arg(leftShortcut.toString()));
	m_rightBtn.setToolTip(tr("Next (%1)").arg(rightShortcut.toString()));
}


} // namespace noemixerr::gui
