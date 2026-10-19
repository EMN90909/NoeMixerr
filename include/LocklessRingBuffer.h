// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LOCKLESS_RING_BUFFER_H
#define NoeMixerr_LOCKLESS_RING_BUFFER_H

#include <QMutex>
#include <QWaitCondition>

#include <ringbuffer/ringbuffer.h>

#include "NoeMixerrTypes.h"

namespace noemixerr
{

//! A convenience layer for a realtime-safe and thread-safe multi-reader ringbuffer
template <class T>
class LocklessRingBuffer
{
	template<class _T>
	friend class LocklessRingBufferReader;
public:
	LocklessRingBuffer(std::size_t sz) : m_buffer(sz)
	{
		m_buffer.touch();	// reserve storage space before realtime operation starts
	}
	~LocklessRingBuffer() = default;

	std::size_t capacity() const {return m_buffer.maximum_eventual_write_space();}
	std::size_t free() const {return m_buffer.write_space();}
	void wakeAll() {m_notifier.wakeAll();}
	std::size_t write(const T *src, std::size_t cnt, bool notify = false)
	{
		std::size_t written = LocklessRingBuffer<T>::m_buffer.write(src, cnt);
		// Let all waiting readers know new data are available.
		if (notify) {LocklessRingBuffer<T>::m_notifier.wakeAll();}
		return written;
	}
	void mlock() { m_buffer.mlock(); }

protected:
	ringbuffer_t<T> m_buffer;
	QWaitCondition m_notifier;
};


//! Wrapper for lockless ringbuffer reader
template <class T>
class LocklessRingBufferReader : public ringbuffer_reader_t<T>
{
public:
	LocklessRingBufferReader(LocklessRingBuffer<T> &rb) :
		ringbuffer_reader_t<T>(rb.m_buffer),
		m_notifier(&rb.m_notifier) {};

	bool empty() const {return !this->read_space();}
	void waitForData()
	{
		QMutex useless_lock;
		useless_lock.lock();
		m_notifier->wait(&useless_lock);
		useless_lock.unlock();
	}
private:
	QWaitCondition *m_notifier;
};


} // namespace noemixerr

#endif // NoeMixerr_LOCKLESS_RING_BUFFER_H
