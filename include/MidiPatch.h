// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2026 Dalton Messmer <messmer.dalton/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_PATCH_H
#define NoeMixerr_MIDI_PATCH_H

#include <cstdint>

namespace noemixerr
{

struct MidiPatch
{
	//! 14-bit bank
	std::uint16_t bank = 0;

	//! 7-bit program
	std::uint8_t program = 0;

	constexpr auto bankMSB() const noexcept -> std::uint8_t { return (bank >> 7) & 0x7F; }
	constexpr auto bankLSB() const noexcept -> std::uint8_t { return bank & 0x7F; }

	constexpr void setBankMSB(std::uint8_t value) noexcept
	{
		bank = ((static_cast<std::uint16_t>(value) & 0x7F) << 7) | (bank & 0x7F);
	}

	constexpr void setBankLSB(std::uint8_t value) noexcept
	{
		bank = (bank & 0x3F80) | (value & 0x7F);
	}
};

} // namespace noemixerr

#endif // NoeMixerr_MIDI_PATCH_H
