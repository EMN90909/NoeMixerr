// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_TYPES_H
#define NoeMixerr_TYPES_H

#include <cstdint>


namespace noemixerr
{

using bar_t         = std::int32_t;
using tick_t        = std::int32_t;
using volume_t      = std::uint8_t;
using panning_t     = std::int8_t;

using sample_t      = float;         // standard sample-type
using int_sample_t  = std::int16_t;  // 16-bit-int-sample

using sample_rate_t = std::uint32_t; // sample-rate
using f_cnt_t       = std::uint64_t; // standard frame-count
using ch_cnt_t      = std::uint16_t; // audio channel index/count (0-MaxChannelsPerAudioBuffer)
using bpm_t         = std::uint16_t; // tempo (MIN_BPM to MAX_BPM)
using bitrate_t     = std::uint16_t; // bitrate in kbps
using mix_ch_t      = std::uint16_t; // Mixer-channel (0 to MAX_CHANNEL)
using group_cnt_t   = std::uint8_t;  // channel group index/count (0-MaxGroupsPerAudioBuffer)

using jo_id_t       = std::uint32_t; // (unique) ID of a journalling object

} // namespace noemixerr

#endif // NoeMixerr_TYPES_H
