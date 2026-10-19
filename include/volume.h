// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_VOLUME_H
#define NoeMixerr_VOLUME_H

#include "NoeMixerrTypes.h"

namespace noemixerr
{


constexpr volume_t MinVolume = 0;
constexpr volume_t MaxVolume = 200;
constexpr volume_t DefaultVolume = 100;

struct StereoVolumeVector
{
	float vol[2];
};

} // namespace noemixerr

#endif // NoeMixerr_VOLUME_H
