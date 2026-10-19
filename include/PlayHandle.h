// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PLAY_HANDLE_H
#define NoeMixerr_PLAY_HANDLE_H

#include <QList>
#include <QMutex>

#include "noemixerr_export.h"

#include "Flags.h"
#include "ThreadableJob.h"
#include "NoeMixerrTypes.h"

class QThread;

namespace noemixerr
{

class Track;
class AudioBusHandle;
class SampleFrame;

class NOEMIXERR_EXPORT PlayHandle : public ThreadableJob
{
public:
	enum class Type
	{
		NotePlayHandle = 0x01,
		InstrumentPlayHandle = 0x02,
		SamplePlayHandle = 0x04,
		PresetPreviewHandle = 0x08
	} ;
	using Types = Flags<Type>;

	constexpr static std::size_t MaxNumber = 1024;

	PlayHandle( const Type type, f_cnt_t offset = 0 );

	PlayHandle & operator = ( PlayHandle & p )
	{
		m_type = p.m_type;
		m_offset = p.m_offset;
		m_affinity = p.m_affinity;
		m_usesBuffer = p.m_usesBuffer;
		m_audioBusHandle = p.m_audioBusHandle;
		return *this;
	}

	virtual ~PlayHandle();

	virtual bool affinityMatters() const
	{
		return false;
	}

	const QThread* affinity() const
	{
		return m_affinity;
	}

	Type type() const
	{
		return m_type;
	}

	// required for ThreadableJob
	void doProcessing() override;

	bool requiresProcessing() const override
	{
		return !isFinished();
	}

	void lock()
	{
		m_processingLock.lock();
	}
	void unlock()
	{
		m_processingLock.unlock();
	}
	bool tryLock()
	{
		return m_processingLock.tryLock();
	}
	virtual void play( SampleFrame* buffer ) = 0;
	virtual bool isFinished() const = 0;

	// returns the frameoffset at the start of the playhandle,
	// ie. how many empty frames should be inserted at the start of the first period
	f_cnt_t offset() const
	{
		return m_offset;
	}

	void setOffset( f_cnt_t _offset )
	{
		m_offset = _offset;
	}


	virtual bool isFromTrack( const Track * _track ) const = 0;

	bool usesBuffer() const
	{
		return m_usesBuffer;
	}
	
	void setUsesBuffer( const bool b )
	{
		m_usesBuffer = b;
	}
	
	AudioBusHandle* audioBusHandle()
	{
		return m_audioBusHandle;
	}
	
	void setAudioBusHandle(AudioBusHandle* busHandle)
	{
		m_audioBusHandle = busHandle;
	}
	
	void releaseBuffer();
	
	SampleFrame* buffer();

private:
	Type m_type;
	f_cnt_t m_offset;
	QThread* m_affinity;
	QMutex m_processingLock;
	SampleFrame* m_playHandleBuffer;
	bool m_bufferReleased;
	bool m_usesBuffer;
	AudioBusHandle* m_audioBusHandle;
} ;

using PlayHandleList = QList<PlayHandle*>;
using ConstPlayHandleList = QList<const PlayHandle*>;

NoeMixerr_DECLARE_OPERATORS_FOR_FLAGS(PlayHandle::Type)

} // namespace noemixerr

#endif // NoeMixerr_PLAY_HANDLE_H
