// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_SAMPLE_RECORDER_H
#define NoeMixerr_AUDIO_SAMPLE_RECORDER_H

#include <QList>
#include <QPair>
#include <memory>

#include "AudioDevice.h"

namespace noemixerr
{

class SampleBuffer;


class AudioSampleRecorder : public AudioDevice
{
public:
	AudioSampleRecorder( const ch_cnt_t _channels, bool & _success_ful, AudioEngine* audioEngine );
	~AudioSampleRecorder() override;

	f_cnt_t framesRecorded() const;
	std::shared_ptr<const SampleBuffer> createSampleBuffer();

private:
	void writeBuffer(const SampleFrame* _ab, const f_cnt_t _frames);

	using BufferList = QList<QPair<SampleFrame*, f_cnt_t>>;
	BufferList m_buffers;

} ;

} // namespace noemixerr

#endif // NoeMixerr_AUDIO_SAMPLE_RECORDER_H
