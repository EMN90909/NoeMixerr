// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2022 Dominic Clark <mrdomclark/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_RAII_HELPERS_H
#define NoeMixerr_RAII_HELPERS_H

#include <cstddef>
#include <memory>


namespace noemixerr
{

template<typename T, T Null>
class NullableResource
{
public:
	NullableResource() = default;
	NullableResource(std::nullptr_t) noexcept { }
	NullableResource(T value) noexcept : m_value{value} { }
	operator T() const noexcept { return m_value; }
	explicit operator bool() const noexcept { return m_value != Null; }
	friend bool operator==(NullableResource a, NullableResource b) noexcept { return a.m_value == b.m_value; }
	friend bool operator==(NullableResource a, T b) noexcept { return a.m_value == b; }
	friend bool operator==(T a, NullableResource b) noexcept { return a == b.m_value; }
	friend bool operator!=(NullableResource a, NullableResource b) noexcept { return a.m_value != b.m_value; }
	friend bool operator!=(NullableResource a, T b) noexcept { return a.m_value != b; }
	friend bool operator!=(T a, NullableResource b) noexcept { return a != b.m_value; }

private:
	T m_value = Null;
};

template<typename T, T Null, auto Deleter>
struct NullableResourceDeleter
{
	using pointer = NullableResource<T, Null>;
	void operator()(T value) const noexcept { Deleter(value); }
};

template<typename T, T Null, auto Deleter>
using UniqueNullableResource = std::unique_ptr<T, NullableResourceDeleter<T, Null, Deleter>>;

} // namespace noemixerr

#endif // NoeMixerr_RAII_HELPERS_H
