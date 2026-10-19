// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Dominic Clark
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_FLAGS_H
#define NoeMixerr_FLAGS_H

#include <type_traits>

namespace noemixerr {

template<typename T>
class Flags
{
	static_assert(std::is_enum_v<T>, "noemixerr::Flags can only be used with enum types");

public:
	using EnumType = T;
	using UnderlyingType = std::underlying_type_t<T>;

	constexpr Flags() = default;

	constexpr Flags(T value) : // Intentionally not explicit
		m_value{static_cast<UnderlyingType>(value)}
	{}

	constexpr explicit Flags(UnderlyingType value) :
		m_value{value}
	{}

	constexpr auto testAll(Flags flags) const -> bool { return (*this & flags) == flags; }
	constexpr auto testAny(Flags flags) const -> bool { return (*this & flags) != Flags{}; }
	constexpr auto testFlag(EnumType flag) const -> bool { return static_cast<bool>(*this & flag); }

	constexpr auto operator~() const -> Flags { return Flags{~m_value}; }
	friend constexpr auto operator&(Flags l, Flags r) -> Flags { return Flags{l.m_value & r.m_value}; }
	friend constexpr auto operator|(Flags l, Flags r) -> Flags { return Flags{l.m_value | r.m_value}; }
	friend constexpr auto operator^(Flags l, Flags r) -> Flags { return Flags{l.m_value ^ r.m_value}; }
	friend constexpr auto operator+(Flags l, Flags r) -> Flags { return Flags{l.m_value | r.m_value}; }
	friend constexpr auto operator-(Flags l, Flags r) -> Flags { return Flags{l.m_value & ~r.m_value}; }

	constexpr auto operator&=(Flags f) -> Flags& { m_value &= f.m_value; return *this; }
	constexpr auto operator|=(Flags f) -> Flags& { m_value |= f.m_value; return *this; }
	constexpr auto operator^=(Flags f) -> Flags& { m_value ^= f.m_value; return *this; }
	constexpr auto operator+=(Flags f) -> Flags& { m_value |= f.m_value; return *this; }
	constexpr auto operator-=(Flags f) -> Flags& { m_value &= ~f.m_value; return *this; }

	constexpr explicit operator UnderlyingType() const { return m_value; } // TODO C++23: explicit(std::is_scoped_enum<T>)
	constexpr explicit operator bool() const { return m_value != 0; }

	friend constexpr auto operator==(Flags l, Flags r) -> bool = default;

private:
	UnderlyingType m_value = 0;
};

#define NoeMixerr_DECLARE_OPERATORS_FOR_FLAGS(type) \
constexpr inline auto operator|(type l, type r) -> ::noemixerr::Flags<type> { return ::noemixerr::Flags{l} | ::noemixerr::Flags{r}; }

} // namespace noemixerr

#endif // NoeMixerr_FLAGS_H
