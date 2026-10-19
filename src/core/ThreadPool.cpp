// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024 saker
// See LICENSE.txt and doc/AUTHORS for original authors and license.

#include "ThreadPool.h"

#include <cassert>

namespace noemixerr {
ThreadPool::ThreadPool(size_t numWorkers)
{
	assert(numWorkers > 0);

	m_workers.reserve(numWorkers);
	for (size_t i = 0; i < numWorkers; ++i)
	{
		m_workers.emplace_back([this] { run(); });
	}
}

ThreadPool::~ThreadPool()
{
	{
		const auto lock = std::unique_lock{m_runMutex};
		m_done = true;
	}

	m_runCond.notify_all();

	for (auto& worker : m_workers)
	{
		if (worker.joinable()) { worker.join(); }
	}
}

auto ThreadPool::numWorkers() const -> size_t
{
	return m_workers.size();
}

void ThreadPool::run()
{
	while (!m_done)
	{
		std::function<void()> task;
		{
			auto lock = std::unique_lock{m_runMutex};
			m_runCond.wait(lock, [this] { return !m_queue.empty() || m_done; });

			if (m_done) { break; }
			task = m_queue.front();
			m_queue.pop();
		}
		task();
	}
}

auto ThreadPool::instance() -> ThreadPool&
{
	static auto s_pool = ThreadPool{s_numWorkers};
	return s_pool;
}

} // namespace noemixerr
