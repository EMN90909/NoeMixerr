// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020-2020 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDIEVENTTOBYTESEQ_H
#define NoeMixerr_MIDIEVENTTOBYTESEQ_H

#include <cstddef>
#include <cstdint>

#include "noemixerr_export.h"


namespace noemixerr
{

//! @brief Write MIDI event into byte sequence.
//!
//! Conforming to http://lv2plug.in/ns/ext/midi#MidiEvent
//!
//! @param ev The MIDI event to write
//! @param data Pointer to the target buffer for the byte sequence. Must point to existing memory with at least 3 bytes
//! size.
//! @param bufsize Available size of the target buffer.
//! @return Used size of the target buffer, or 0 if the MidiEvent could not be converted.
std::size_t NOEMIXERR_EXPORT writeToByteSeq(const class MidiEvent& ev, uint8_t* data, std::size_t bufsize);

} // namespace noemixerr

#endif // NoeMixerr_MIDIEVENTTOBYTESEQ_H
