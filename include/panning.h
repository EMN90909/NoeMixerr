// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PANNING_H
#define NoeMixerr_PANNING_H

#include "NoeMixerrTypes.h"
#include "Midi.h"
#include "volume.h"

#include <cmath>

namespace noemixerr
{

inline constexpr panning_t PanningRight = 100;
inline constexpr panning_t PanningLeft = -PanningRight;
inline constexpr panning_t PanningCenter = 0;
inline constexpr panning_t DefaultPanning = PanningCenter;

inline StereoVolumeVector panningToVolumeVector( panning_t _p,
							float _scale = 1.0f )
{
	StereoVolumeVector v = { { _scale, _scale } };
	const float pf = _p / 100.0f;
	v.vol[_p >= PanningCenter ? 0 : 1] *= 1.0f - std::abs(pf);
	return v;
}


inline int panningToMidi( panning_t _p )
{
	return MidiMinPanning + (int) (
			  ( (float)( _p - PanningLeft ) ) /
			  ( (float)( PanningRight - PanningLeft ) ) *
			  ( (float)( MidiMaxPanning - MidiMinPanning ) ) );
}


} // namespace noemixerr

#endif // NoeMixerr_PANNING_H
