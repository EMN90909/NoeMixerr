// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "MixerChannelLcdSpinBox.h"

#include <QInputDialog>
#include <QMouseEvent>

#include "CaptionMenu.h"
#include "MixerView.h"
#include "GuiApplication.h"
#include "TrackView.h"

namespace noemixerr::gui
{


void MixerChannelLcdSpinBox::setTrackView(TrackView * tv)
{
	m_tv = tv;
}

void MixerChannelLcdSpinBox::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (!(event->modifiers() & Qt::ShiftModifier) &&
		!(event->modifiers() & Qt::ControlModifier))
	{
		enterValue();
		return;
	}

	getGUI()->mixerView()->setCurrentMixerChannel(model()->value());

	getGUI()->mixerView()->parentWidget()->show();
	getGUI()->mixerView()->show();// show Mixer window
	getGUI()->mixerView()->setFocus();// set focus to Mixer window
	//engine::getMixerView()->raise();
}

void MixerChannelLcdSpinBox::contextMenuEvent(QContextMenuEvent* event)
{
	// for the case, the user clicked right while pressing left mouse-
	// button, the context-menu appears while mouse-cursor is still hidden
	// and it isn't shown again until user does something which causes
	// an QApplication::restoreOverrideCursor()-call...
	mouseReleaseEvent(nullptr);

	QPointer<CaptionMenu> contextMenu = new CaptionMenu(model()->displayName(), this);

	if (QMenu *mixerMenu = m_tv->createMixerMenu(
		tr("Assign to:"), tr("New Mixer Channel")))
	{
		contextMenu->addMenu(mixerMenu);

		contextMenu->addSeparator();
	}
	addDefaultActions(contextMenu);
	contextMenu->exec(QCursor::pos());
}

void MixerChannelLcdSpinBox::enterValue()
{
	const auto val = model()->value();
	const auto min = model()->minValue();
	const auto max = model()->maxValue();
	const auto step = model()->step<int>();
	const auto label = tr("Please enter a new value between %1 and %2:").arg(min).arg(max);

	auto ok = false;
	const auto newVal = QInputDialog::getInt(this, tr("Set value"), label, val, min, max, step, &ok);

	if (ok) { model()->setValue(newVal); }
}

} // namespace noemixerr::gui
