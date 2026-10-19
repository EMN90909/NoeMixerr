// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PITCH_H
#define NoeMixerr_PITCH_H

#include <cstdint>

namespace noemixerr
{

using pitch_t = int16_t;

constexpr pitch_t CentsPerSemitone = 100;
constexpr pitch_t MinPitchDefault = -CentsPerSemitone;
constexpr pitch_t MaxPitchDefault = CentsPerSemitone;
constexpr pitch_t DefaultPitch = 0;


} // namespace noemixerr

#endif // NoeMixerr_PITCH_H
