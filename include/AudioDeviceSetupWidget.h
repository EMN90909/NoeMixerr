// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2015 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2023- Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_AUDIO_DEVICE_SETUP_WIDGET_H
#define NoeMixerr_GUI_AUDIO_DEVICE_SETUP_WIDGET_H

#include <QGroupBox>

namespace noemixerr::gui
{

class AudioDeviceSetupWidget : public QGroupBox
{
    Q_OBJECT
public:
	AudioDeviceSetupWidget( const QString & _caption, QWidget * _parent );

	~AudioDeviceSetupWidget() override = default;

	virtual void saveSettings() = 0;

	virtual void show();
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_AUDIO_DEVICE_SETUP_WIDGET_H
