// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 
#include "PlayHandle.h"
#include "AudioEngine.h"
#include "BufferManager.h"
#include "Engine.h"

#include <QThread>


namespace noemixerr
{

PlayHandle::PlayHandle(const Type type, f_cnt_t offset) :
		m_type(type),
		m_offset(offset),
		m_affinity(QThread::currentThread()),
		m_playHandleBuffer(BufferManager::acquire()),
		m_bufferReleased(true),
		m_usesBuffer(true)
{
}


PlayHandle::~PlayHandle()
{
	BufferManager::release(m_playHandleBuffer);
}


void PlayHandle::doProcessing()
{
	if( m_usesBuffer )
	{
		m_bufferReleased = false;
		zeroSampleFrames(m_playHandleBuffer, Engine::audioEngine()->framesPerPeriod());
		play( buffer() );
	}
	else
	{
		play( nullptr );
	}
}


void PlayHandle::releaseBuffer()
{
	m_bufferReleased = true;
}

SampleFrame* PlayHandle::buffer()
{
	return m_bufferReleased ? nullptr : m_playHandleBuffer;
};

} // namespace noemixerr