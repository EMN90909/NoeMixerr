// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "MidiSetupWidget.h"

#include <QFormLayout>
#include <QLineEdit>

#include "ConfigManager.h"


namespace noemixerr::gui
{


MidiSetupWidget::MidiSetupWidget(const QString & caption, const QString & configSection,
	const QString & devName, QWidget * parent) :
	QGroupBox(QGroupBox::tr("Settings for %1").arg(tr(caption.toUtf8())), parent),
	m_configSection(configSection),
	m_device(nullptr)
{
	// supply devName=QString() (distinct from QString(""))
	// to indicate that there is no editable device field
	if (!devName.isNull())
	{
		QFormLayout * form = new QFormLayout(this);

		m_device = new QLineEdit(devName, this);

		form->addRow(tr("Device"), m_device);
	}
}

void MidiSetupWidget::saveSettings()
{
	if (!m_configSection.isEmpty() && m_device)
	{
		ConfigManager::inst()->setValue(m_configSection, "device",
				m_device->text());
	}
}

void MidiSetupWidget::show()
{
	// the setup widget should only be visible if the device has some configurable attributes
	bool visible = !m_configSection.isEmpty();
	parentWidget()->setVisible(visible);
	QWidget::setVisible(visible);
}


} // namespace noemixerr::gui
