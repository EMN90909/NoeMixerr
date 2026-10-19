// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2022-2022 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LV2WORKER_H
#define LV2WORKER_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_LV2

#include <lv2/worker/worker.h>
#include <thread>
#include <vector>

#include "LocklessRingBuffer.h"
#include "NoeMixerrSemaphore.h"

namespace noemixerr
{

/**
	Worker container
*/
class Lv2Worker
{
public:
	// CTOR/DTOR/feature access
	Lv2Worker(Semaphore* commonWorkLock, bool threaded);
	~Lv2Worker();
	void setHandle(LV2_Handle handle);
	void setInterface(const LV2_Worker_Interface* newInterface);
	LV2_Worker_Schedule* feature() { return &m_scheduleFeature; }

	// public API
	void emitResponses();
	void notifyPluginThatRunFinished()
	{
		if(m_interface->end_run) { m_interface->end_run(m_scheduleFeature.handle); }
	}

	// to be called only by static functions
	LV2_Worker_Status scheduleWork(uint32_t size, const void* data);
	LV2_Worker_Status respond(uint32_t size, const void* data);

private:
	// functions
	void workerFunc();
	std::size_t bufferSize() const;  //!< size of internal buffers

	// parameters
	const bool m_threaded;
	const LV2_Worker_Interface* m_interface = nullptr;
	LV2_Handle m_handle = nullptr;
	LV2_Worker_Schedule m_scheduleFeature;

	// threading/synchronization
	std::thread m_thread;
	std::vector<char> m_response;  //!< buffer where single requests from m_requests are unpacked
	LocklessRingBuffer<char> m_requests, m_responses;  //!< ringbuffer to queue multiple requests
	LocklessRingBufferReader<char> m_requestsReader, m_responsesReader;
	std::atomic<bool> m_exit = false;  //!< Whether the worker function should keep looping
	Semaphore m_sem;
	Semaphore* m_workLock;
};


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

#endif // LV2WORKER_H

