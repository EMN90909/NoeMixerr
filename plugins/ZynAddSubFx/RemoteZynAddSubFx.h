// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef REMOTE_ZYNADDSUBFX_H
#define REMOTE_ZYNADDSUBFX_H

#include "RemotePluginBase.h"

namespace noemixerr
{


enum ZasfRemoteMessageIDs
{
	IdZasfPresetDirectory = RemoteMessageIDs::IdUserBase,
	IdZasfNoeMixerrWorkingDirectory,
	IdZasfSetPitchWheelBendRange
} ;


} // namespace noemixerr

#endif
