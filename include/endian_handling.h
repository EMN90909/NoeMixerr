// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2026      Dalton Messmer <messmer.dalton/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_ENDIAN_HANDLING_H
#define NoeMixerr_ENDIAN_HANDLING_H

#include <bit>
#include <type_traits>

namespace noemixerr {

constexpr bool isLittleEndian() noexcept
{
	return std::endian::native == std::endian::little;
}

constexpr bool isBigEndian() noexcept
{
	return std::endian::native == std::endian::big;
}

//! TODO C++23: Use std::byteswap
template<typename Int>
	requires (sizeof(Int) <= 4 && std::is_integral_v<Int>)
constexpr Int byteswap(Int i) noexcept
{
	if constexpr (sizeof(Int) == 1) { return i; }
	else if constexpr (sizeof(Int) == 2)
	{
		return ((i & 0xFF) << 8) | ((i >> 8) & 0xFF);
	}
	else if constexpr (sizeof(Int) == 4)
	{
		return ((i & 0xff000000) >> 24)
		     | ((i & 0x00ff0000) >> 8)
		     | ((i & 0x0000ff00) << 8)
		     | ((i & 0x000000ff) << 24);
	}
	else { static_assert(sizeof(Int) == 1, "invalid size"); }
}

template<std::endian e, typename Int>
constexpr Int byteswapIf(Int i) noexcept
{
	if constexpr (std::endian::native == e) { return byteswap(i); }
	else { return i; }
}

template<typename Int>
constexpr Int byteswapIfBE(Int i) noexcept { return byteswapIf<std::endian::big>(i); }

template<typename Int>
constexpr Int byteswapIfLE(Int i) noexcept { return byteswapIf<std::endian::little>(i); }

} // namespace noemixerr

#endif // NoeMixerr_ENDIAN_HANDLING_H
