// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2022-2022 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Lv2Worker.h"

#include <cassert>

#ifdef NoeMixerr_HAVE_LV2



namespace noemixerr
{


// static wrappers

static LV2_Worker_Status
staticWorkerRespond(LV2_Worker_Respond_Handle handle,
	uint32_t size, const void* data)
{
	Lv2Worker* worker = static_cast<Lv2Worker*>(handle);
	return worker->respond(size, data);
}




std::size_t Lv2Worker::bufferSize() const
{
	// ardour uses this fixed size for ALSA:
	return 8192 * 4;
	// for jack, they use 4 * jack_port_type_get_buffer_size (..., JACK_DEFAULT_MIDI_TYPE)
	// (possible extension for AudioDevice)
}




Lv2Worker::Lv2Worker(Semaphore* commonWorkLock, bool threaded) :
	m_threaded(threaded),
	m_response(bufferSize()),
	m_requests(bufferSize()),
	m_responses(bufferSize()),
	m_requestsReader(m_requests),
	m_responsesReader(m_responses),
	m_sem(0),
	m_workLock(commonWorkLock)
{
	m_scheduleFeature.handle = static_cast<LV2_Worker_Schedule_Handle>(this);
	m_scheduleFeature.schedule_work = [](LV2_Worker_Schedule_Handle handle,
		uint32_t size, const void* data) -> LV2_Worker_Status
		{
			Lv2Worker* worker = static_cast<Lv2Worker*>(handle);
			return worker->scheduleWork(size, data);
		};

	if (threaded) { m_thread = std::thread(&Lv2Worker::workerFunc, this); }

	m_requests.mlock();
	m_responses.mlock();
}




void Lv2Worker::setHandle(LV2_Handle handle)
{
	assert(handle);
	m_handle = handle;
}




void Lv2Worker::setInterface(const LV2_Worker_Interface* newInterface)
{
	assert(newInterface);
	m_interface = newInterface;
}




Lv2Worker::~Lv2Worker()
{
	m_exit = true;
	if(m_threaded) {
		m_sem.post();
		m_thread.join();
	}
}




// Let the worker send responses to the audio thread
LV2_Worker_Status Lv2Worker::respond(uint32_t size, const void* data)
{
	if(m_threaded)
	{
		if(m_responses.free() < sizeof(size) + size)
		{
			return LV2_WORKER_ERR_NO_SPACE;
		}
		else
		{
			m_responses.write((const char*)&size, sizeof(size));
			if(size && data) { m_responses.write((const char*)data, size); }
		}
	}
	else
	{
		assert(m_handle);
		assert(m_interface);
		m_interface->work_response(m_handle, size, data);
	}
	return LV2_WORKER_SUCCESS;
}




// Let the worker receive work from the audio thread and "work" on it
void Lv2Worker::workerFunc()
{
	std::vector<char> buf;
	uint32_t size;
	while (true) {
		m_sem.wait();
		if (m_exit) { break; }

		const std::size_t readSpace = m_requestsReader.read_space();
		if (readSpace <= sizeof(size)) { continue; } // (should not happen)

		m_requestsReader.read(sizeof(size)).copy((char*)&size, sizeof(size));
		assert(size <= readSpace - sizeof(size));
		if(size > buf.size()) { buf.resize(size); }
		if(size) { m_requestsReader.read(size).copy(buf.data(), size); }

		assert(m_handle);
		assert(m_interface);
		m_workLock->wait();
		m_interface->work(m_handle, staticWorkerRespond, this, size, buf.data());
		m_workLock->post();
	}
}




// Let the audio thread schedule work for the worker
LV2_Worker_Status Lv2Worker::scheduleWork(uint32_t size, const void *data)
{
	if (m_threaded)
	{
		if(m_requests.free() < sizeof(size) + size)
		{
			return LV2_WORKER_ERR_NO_SPACE;
		}
		else
		{
			// Schedule a request to be executed by the worker thread
			m_requests.write((const char*)&size, sizeof(size));
			if(size && data) { m_requests.write((const char*)data, size); }
			m_sem.post();
		}
	}
	else
	{
		assert(m_handle);
		assert(m_interface);
		// Execute work immediately in this thread
		m_workLock->wait();
		m_interface->work(m_handle, staticWorkerRespond, this, size, data);
		m_workLock->post();
	}

	return LV2_WORKER_SUCCESS;
}




// Let the audio thread read incoming worker responses, and process it
void Lv2Worker::emitResponses()
{
	std::size_t read_space = m_responsesReader.read_space();
	uint32_t size;
	while (read_space > sizeof(size))
	{
		assert(m_handle);
		assert(m_interface);
		m_responsesReader.read(sizeof(size)).copy((char*)&size, sizeof(size));
		if(size) { m_responsesReader.read(size).copy(m_response.data(), size); }
		m_interface->work_response(m_handle, size, m_response.data());
		read_space -= sizeof(size) + size;
	}
}


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2
