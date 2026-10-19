// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Csaba Hruska <csaba.hruska/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_SAMPLE_RECORD_HANDLE_H
#define NoeMixerr_SAMPLE_RECORD_HANDLE_H

#include <QList>
#include <QPair>
#include <memory>

#include "PlayHandle.h"
#include "TimePos.h"

namespace noemixerr
{


class PatternTrack;
class SampleBuffer;
class SampleClip;
class Track;


class SampleRecordHandle : public PlayHandle
{
public:
	SampleRecordHandle( SampleClip* clip );
	~SampleRecordHandle() override;

	void play( SampleFrame* _working_buffer ) override;
	bool isFinished() const override;

	bool isFromTrack( const Track * _track ) const override;

	f_cnt_t framesRecorded() const;
	std::shared_ptr<const SampleBuffer> createSampleBuffer();


private:
	virtual void writeBuffer( const SampleFrame* _ab,
						const f_cnt_t _frames );

	using bufferList = QList<QPair<SampleFrame*, f_cnt_t>>;
	bufferList m_buffers;
	f_cnt_t m_framesRecorded;
	TimePos m_minLength;

	Track * m_track;
	PatternTrack* m_patternTrack;
	SampleClip * m_clip;

} ;


} // namespace noemixerr

#endif // NoeMixerr_SAMPLE_RECORD_HANDLE_H
