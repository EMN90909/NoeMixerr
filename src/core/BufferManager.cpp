// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 Lukas W <lukaswhl/at/gmail.com>
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "BufferManager.h"

#include "SampleFrame.h"


namespace noemixerr
{

f_cnt_t BufferManager::s_framesPerPeriod;

void BufferManager::init( f_cnt_t fpp )
{
	s_framesPerPeriod = fpp;
}


SampleFrame* BufferManager::acquire()
{
	return new SampleFrame[s_framesPerPeriod];
}



void BufferManager::release( SampleFrame* buf )
{
	delete[] buf;
}

} // namespace noemixerr
