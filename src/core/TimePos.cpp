// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "TimePos.h"

#include "MeterModel.h"

namespace noemixerr
{

TimeSig::TimeSig( int num, int denom ) :
	m_num(num),
	m_denom(denom)
{
}

TimeSig::TimeSig( const MeterModel &model ) :
	m_num(model.getNumerator()),
	m_denom(model.getDenominator())
{
}

TimePos::TimePos( const bar_t bar, const tick_t ticks ) :
	m_ticks( bar * s_ticksPerBar + ticks )
{
}

TimePos::TimePos( const tick_t ticks ) :
	m_ticks( ticks )
{
}

TimePos TimePos::quantize(float bars, bool forceRoundDown) const
{
	//The intervals we should snap to, our new position should be a factor of this
	int interval = s_ticksPerBar * bars;
	//The lower position we could snap to
	int lowPos = m_ticks / interval;
	//Offset from the lower position
	int offset = m_ticks % interval;
	//1 if we should snap up, 0 if we shouldn't
	// Ternary expression is making sure that the snap happens in the direction to
	// the right even if m_ticks is negative and the offset is exactly half-way
	// More details on issue #5840 and PR #5847
	int snapUp = forceRoundDown || ((2 * offset) == -interval)
		? 0
		: (2 * offset) / interval;

	return (lowPos + snapUp) * interval;
}

} // namespace noemixerr
