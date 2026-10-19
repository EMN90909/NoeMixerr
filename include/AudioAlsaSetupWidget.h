// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2015 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_AUDIO_ALSA_SETUP_WIDGET_H
#define NoeMixerr_GUI_AUDIO_ALSA_SETUP_WIDGET_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_ALSA

#include "AudioDeviceSetupWidget.h"

#include "AudioAlsa.h"


class QComboBox;

namespace noemixerr::gui
{

class LcdSpinBox;

class AudioAlsaSetupWidget : public AudioDeviceSetupWidget
{
	Q_OBJECT

public:
	AudioAlsaSetupWidget( QWidget * _parent );
	~AudioAlsaSetupWidget() override;

	void saveSettings() override;

public slots:
	void onCurrentIndexChanged(int index);

private:
	QComboBox * m_deviceComboBox;
	LcdSpinBox * m_channels;

	int m_selectedDevice;
	AudioAlsa::DeviceInfoCollection m_deviceInfos;
};

} // namespace noemixerr::gui

#endif // NoeMixerr_HAVE_ALSA

#endif // NoeMixerr_GUI_AUDIO_ALSA_SETUP_WIDGET_H
