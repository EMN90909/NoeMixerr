// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MICRO_TIMER_H
#define NoeMixerr_MICRO_TIMER_H

#include <chrono>

namespace noemixerr
{

class MicroTimer
{
	using time_point = std::chrono::steady_clock::time_point;

public:
	MicroTimer();
	~MicroTimer() = default;

	void reset();
	int elapsed() const;

private:
	time_point begin;
} ;


} // namespace noemixerr

#endif // NoeMixerr_MICRO_TIMER_H
