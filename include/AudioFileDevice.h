// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_FILE_DEVICE_H
#define NoeMixerr_AUDIO_FILE_DEVICE_H

#include <QFile>

#include "AudioDevice.h"
#include "OutputSettings.h"

namespace noemixerr
{

class AudioFileDevice : public AudioDevice
{
public:
	AudioFileDevice(OutputSettings const & outputSettings,
			const ch_cnt_t _channels, const QString & _file,
			AudioEngine* audioEngine );
	~AudioFileDevice() override;

	QString outputFile() const
	{
		return m_outputFile.fileName();
	}

	OutputSettings const & getOutputSettings() const { return m_outputSettings; }

	//! Write `size` sample frames from `buf` into the output file.
	virtual void writeBuffer(const SampleFrame* buf, const f_cnt_t frames) = 0;

protected:
	int writeData( const void* data, int len );

	inline bool outputFileOpened() const
	{
		return m_outputFile.isOpen();
	}

	inline int outputFileHandle() const
	{
		return m_outputFile.handle();
	}

private:
	void startProcessingImpl() override {}
	void stopProcessingImpl() override {}

	QFile m_outputFile;
	OutputSettings m_outputSettings;
} ;

using AudioFileDeviceInstantiaton
	= AudioFileDevice* (*)(const QString&, const OutputSettings&, const ch_cnt_t, AudioEngine*, bool&);

} // namespace noemixerr

#endif // NoeMixerr_AUDIO_FILE_DEVICE_H
