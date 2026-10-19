// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_BUFFER_MANAGER_H
#define NoeMixerr_BUFFER_MANAGER_H

#include "noemixerr_export.h"
#include "NoeMixerrTypes.h"

namespace noemixerr
{

class SampleFrame;

class NOEMIXERR_EXPORT BufferManager
{
public:
	static void init( f_cnt_t fpp );
	static SampleFrame* acquire();
	static void release( SampleFrame* buf );

private:
	static f_cnt_t s_framesPerPeriod;
};


} // namespace noemixerr

#endif // NoeMixerr_BUFFER_MANAGER_H
