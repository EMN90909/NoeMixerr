// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_ALSA_H
#define NoeMixerr_AUDIO_ALSA_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_ALSA

// older ALSA-versions might require this
#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>
#include <QThread>

#include "AudioDevice.h"

namespace noemixerr
{

class AudioAlsa : public QThread, public AudioDevice
{
	Q_OBJECT
public:
	/**
	 * @brief Contains the relevant information about available ALSA devices
	 */
	class DeviceInfo
	{
	public:
		DeviceInfo(QString const & deviceName, QString const & deviceDescription) :
			m_deviceName(deviceName),
			m_deviceDescription(deviceDescription)
		{}
		~DeviceInfo() = default;

		QString const & getDeviceName() const { return m_deviceName; }
		QString const & getDeviceDescription() const { return m_deviceDescription; }

	private:
		QString m_deviceName;
		QString m_deviceDescription;

	};

	using DeviceInfoCollection = std::vector<DeviceInfo>;

public:
	AudioAlsa( bool & _success_ful, AudioEngine* audioEngine );
	~AudioAlsa() override;

	inline static QString name()
	{
		return QT_TRANSLATE_NOOP( "AudioDeviceSetupWidget",
			"ALSA (Advanced Linux Sound Architecture)" );
	}

	static QString probeDevice();

	//! @brief Creates a list of all available devices.
	//!
	//! Uses the hints API of ALSA to collect all devices. This also includes plug devices. The reason to collect these
	//! and not the raw hardware devices (e.g. hw:0,0) is that hardware devices often have a very limited number of
	//! supported formats, etc. Plugs on the other hand are software components that map all types of formats and inputs
	//! to the hardware and therefore they are much more flexible and more what we want.
	//!
	//! @see Further helpful info at [http://jan.newmarch.name/LinuxSound/Sampled/Alsa](https://web.archive.org/web/20211204221331/http://jan.newmarch.name/LinuxSound/Sampled/Alsa/).
	//! @return A collection of devices found on the system.
	static DeviceInfoCollection getAvailableDevices();

private:
	void startProcessingImpl() override;
	void stopProcessingImpl() override;
	void run() override;

	int setHWParams( const ch_cnt_t _channels, snd_pcm_access_t _access );
	int setSWParams();
	int handleError( int _err );


	snd_pcm_t * m_handle;

	snd_pcm_uframes_t m_bufferSize;
	snd_pcm_uframes_t m_periodSize;

	snd_pcm_hw_params_t * m_hwParams;
	snd_pcm_sw_params_t * m_swParams;
} ;

} // namespace noemixerr

#endif // NoeMixerr_HAVE_ALSA

#endif // NoeMixerr_AUDIO_ALSA_H
