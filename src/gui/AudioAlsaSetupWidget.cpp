// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2015 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QComboBox>
#include <QFormLayout>

#include "AudioAlsaSetupWidget.h"

#ifdef NoeMixerr_HAVE_ALSA

#include "ConfigManager.h"
#include "LcdSpinBox.h"
#include "noemixerr_constants.h"

namespace noemixerr::gui
{

AudioAlsaSetupWidget::AudioAlsaSetupWidget( QWidget * _parent ) :
	AudioDeviceSetupWidget( AudioAlsa::name(), _parent ),
	m_selectedDevice(-1)
{
	QFormLayout * form = new QFormLayout(this);

	m_deviceInfos = AudioAlsa::getAvailableDevices();

	QString deviceText = ConfigManager::inst()->value( "audioalsa", "device" );

	m_deviceComboBox = new QComboBox(this);
	for (size_t i = 0; i < m_deviceInfos.size(); ++i)
	{
		AudioAlsa::DeviceInfo const & currentDeviceInfo = m_deviceInfos[i];
		QString comboBoxText = currentDeviceInfo.getDeviceName();
		m_deviceComboBox->addItem(comboBoxText, QVariant(static_cast<uint>(i)));

		QString toolTipText = currentDeviceInfo.getDeviceDescription();
		m_deviceComboBox->setItemData(i, toolTipText, Qt::ToolTipRole);

		if (currentDeviceInfo.getDeviceName() == deviceText)
		{
			m_deviceComboBox->setCurrentIndex(static_cast<int>(i));
		}
	}

	m_selectedDevice = m_deviceComboBox->currentIndex();

	connect(m_deviceComboBox,
			SIGNAL(currentIndexChanged(int)),
			SLOT(onCurrentIndexChanged(int)));

	form->addRow(tr("Device"), m_deviceComboBox);

	auto m = new LcdSpinBoxModel(/* this */);
	m->setRange(DEFAULT_CHANNELS, DEFAULT_CHANNELS);
	m->setStep( 2 );
	m->setValue( ConfigManager::inst()->value( "audioalsa",
							"channels" ).toInt() );

	m_channels = new LcdSpinBox( 1, this );
	m_channels->setModel( m );

	form->addRow(tr("Channels"), m_channels);
}




AudioAlsaSetupWidget::~AudioAlsaSetupWidget()
{
	delete m_channels->model();
}




void AudioAlsaSetupWidget::saveSettings()
{
	QString deviceText;

	if (m_selectedDevice != -1)
	{
		AudioAlsa::DeviceInfo const & selectedDevice = m_deviceInfos[m_selectedDevice];
		deviceText = selectedDevice.getDeviceName();
	}

	ConfigManager::inst()->setValue( "audioalsa", "device", deviceText );
	ConfigManager::inst()->setValue( "audioalsa", "channels",
				QString::number( m_channels->value<int>() ) );
}



void AudioAlsaSetupWidget::onCurrentIndexChanged(int index)
{
	m_selectedDevice = index;
}


} // namespace noemixerr::gui

#endif // NoeMixerr_HAVE_ALSA
