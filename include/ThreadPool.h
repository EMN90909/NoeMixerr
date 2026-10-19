// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024 saker
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_THREAD_POOL_H
#define NoeMixerr_THREAD_POOL_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <tuple>
#include <type_traits>
#include <vector>

namespace noemixerr {
//! A thread pool that can be used for asynchronous processing.
class ThreadPool
{
public:
	//! Destroys the `ThreadPool` object.
	//! This blocks until all workers have finished executing.
	~ThreadPool();

	//! Enqueue function `fn` with arguments `args` to be ran asynchronously.
	template <typename Fn, typename... Args>
	auto enqueue(Fn&& fn, Args&&... args) -> std::future<std::invoke_result_t<Fn, Args...>>
	{
		using ReturnType = std::invoke_result_t<Fn, Args...>;

		auto promise = std::make_shared<std::promise<ReturnType>>();
		auto task = [promise, fn = std::forward<Fn>(fn), args = std::make_tuple(std::forward<Args>(args)...)] 
		{
			if constexpr (!std::is_same_v<ReturnType, void>)
			{
				promise->set_value(std::apply(fn, args));
				return;
			}
			std::apply(fn, args);
			promise->set_value();
		};

		{
			const auto lock = std::unique_lock{m_runMutex};
			m_queue.push(std::move(task));
		}

		m_runCond.notify_one();
		return promise->get_future();
	}

	//! Return the number of worker threads used.
	auto numWorkers() const -> size_t;

	//! Return the global `ThreadPool` instance.
	static auto instance() -> ThreadPool&;

private:
	ThreadPool(size_t numWorkers);
	void run();
	std::vector<std::thread> m_workers;
	std::queue<std::function<void()>> m_queue;
	std::atomic<bool> m_done = false;
	std::condition_variable m_runCond;
	std::mutex m_runMutex;
	inline static size_t s_numWorkers = std::thread::hardware_concurrency();
};
} // namespace noemixerr

#endif // NoeMixerr_THREAD_POOL_H
