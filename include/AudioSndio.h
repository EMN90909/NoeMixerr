// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2010-2016 jackmsr@openbsd.net
// Copyright (c) 2016-2017 David Carlier <devnexen@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_SNDIO_H
#define NoeMixerr_AUDIO_SNDIO_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_SNDIO

#include <QThread>
#include <sndio.h>

#include "AudioDevice.h"
#include "AudioDeviceSetupWidget.h"

class QLineEdit;

namespace noemixerr
{

namespace gui
{
class LcdSpinBox;
}


class AudioSndio : public QThread, public AudioDevice
{
	Q_OBJECT
public:
	AudioSndio( bool & _success_ful, AudioEngine * _audioEngine );
	~AudioSndio() override;

	inline static QString name()
	{
		return QT_TRANSLATE_NOOP( "AudioDeviceSetupWidget", "sndio" );
	}

	class setupWidget : public gui::AudioDeviceSetupWidget
	{
	public:
		setupWidget( QWidget * _parent );
		~setupWidget() override = default;

		void saveSettings() override;

	private:
		QLineEdit * m_device;
		gui::LcdSpinBox * m_channels;
	} ;

private:
	void startProcessingImpl() override;
	void stopProcessingImpl() override;
	void run() override;

	struct sio_hdl *m_hdl;
	struct sio_par m_par;
};

} // namespace noemixerr

#endif // NoeMixerr_HAVE_SNDIO

#endif // NoeMixerr_AUDIO_SNDIO_H
