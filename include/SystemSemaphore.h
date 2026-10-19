// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024 Dominic Clark
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_SYSTEM_SEMAPHORE_H
#define NoeMixerr_SYSTEM_SEMAPHORE_H

#include <memory>
#include <string>

namespace noemixerr {

namespace detail {

class SystemSemaphoreImpl;

} // namespace detail

class SystemSemaphore
{
public:
	SystemSemaphore() noexcept;
	SystemSemaphore(std::string key, unsigned int value);
	explicit SystemSemaphore(std::string key);
	~SystemSemaphore();

	SystemSemaphore(SystemSemaphore&& other) noexcept;
	auto operator=(SystemSemaphore&& other) noexcept -> SystemSemaphore&;

	auto acquire() noexcept -> bool;
	auto release() noexcept -> bool;

	auto key() const noexcept -> const std::string& { return m_key; }

private:
	std::string m_key;
	std::unique_ptr<detail::SystemSemaphoreImpl> m_impl;
};

} // namespace noemixerr

#endif // NoeMixerr_SYSTEM_SEMAPHORE_H
