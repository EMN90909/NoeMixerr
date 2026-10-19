// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2015-2023 Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "LadspaWidgetFactory.h"

#include "LadspaControl.h"
#include "LadspaBase.h"

#include "BarModelEditor.h"
#include "LedCheckBox.h"
#include "TempoSyncBarModelEditor.h"

#include <QHBoxLayout>
#include <QLabel>


namespace noemixerr::gui
{

QWidget * LadspaWidgetFactory::createWidget(LadspaControl * ladspaControl, QWidget * parent)
{
	auto const * port = ladspaControl->port();

	QString const name = port->name;

	switch (port->data_type)
	{
	case BufferDataType::Toggled:
	{
		// The actual check box is put into a widget because LedCheckBox does not play nice with layouts.
		// Putting it directly into a grid layout disables the resizing behavior of all columns where it
		// appears. Hence we put it into the layout of a widget that knows how to play nice with layouts.
		QWidget * widgetWithLayout = new QWidget(parent);
		QHBoxLayout * layout = new QHBoxLayout(widgetWithLayout);
		layout->setContentsMargins(0, 0, 0, 0);
		LedCheckBox * toggle = new LedCheckBox(
			name, parent, QString(), LedCheckBox::LedColor::Green, false);
		toggle->setModel(ladspaControl->toggledModel());
		layout->addWidget(toggle, 0, Qt::AlignLeft);

		return widgetWithLayout;
	}

	case BufferDataType::Integer:
	case BufferDataType::Enum:
	case BufferDataType::Floating:
		return new BarModelEditor(name, ladspaControl->knobModel(), parent);

	case BufferDataType::Time:
		return new TempoSyncBarModelEditor(name, ladspaControl->tempoSyncKnobModel(), parent);

	default:
		return new QLabel(QObject::tr("%1 (unsupported)").arg(name), parent);
	}

	return nullptr;
}

} // namespace noemixerr::gui
