// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017-2018 LMMS Developers
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "PerfLog.h"

#include "noemixerrconfig.h"

#if defined(NoeMixerr_HAVE_SYS_TIMES_H) && defined(NoeMixerr_HAVE_UNISTD_H)
#	define USE_POSIX_TIME
#endif

#ifdef USE_POSIX_TIME
#	include <unistd.h>
#	include <sys/times.h>
#endif


namespace noemixerr
{


PerfTime::PerfTime()
	: m_real(-1)
{
}

clock_t PerfTime::real() const
{
	return m_real;
}

clock_t PerfTime::user() const
{
	return m_user;
}

clock_t PerfTime::system() const
{
	return m_system;
}

bool PerfTime::valid() const
{
	return m_real != -1;
}

PerfTime PerfTime::now()
{
	PerfTime time;
#ifdef USE_POSIX_TIME
	tms t;
	time.m_real = times(&t);
	time.m_user = t.tms_utime;
	time.m_system = t.tms_stime;
	if (time.m_real == -1) { qWarning("PerfTime: now failed"); }
#endif
	return time;
}

clock_t PerfTime::ticksPerSecond()
{
	static long clktck = 0;
#ifdef USE_POSIX_TIME
	if (!clktck) {
		if ((clktck = sysconf(_SC_CLK_TCK)) < 0) {
			qWarning("PerfLog::end sysconf()");
		}
	}
#endif
	return clktck;
}

PerfTime operator-(const PerfTime& lhs, const PerfTime& rhs)
{
	PerfTime diff;
	diff.m_real = lhs.m_real - rhs.m_real;
	diff.m_user = lhs.m_user - rhs.m_user;
	diff.m_system = lhs.m_system - rhs.m_system;
	return diff;
}

PerfLogTimer::PerfLogTimer(const QString& what)
	: name(what)
{
	begin();
}

PerfLogTimer::~PerfLogTimer()
{
	end();
}

void PerfLogTimer::begin()
{
	begin_time = PerfTime::now();
}

void PerfLogTimer::end()
{
	if (! begin_time.valid()) {
		return;
	}

	long clktck = PerfTime::ticksPerSecond();

	PerfTime d = PerfTime::now() - begin_time;
	qWarning("PERFLOG | %20s | %.2fuser, %.2fsystem %.2felapsed",
			 qPrintable(name),
			 d.user() / (double)clktck,
			 d.system() / (double)clktck,
			 d.real() / (double)clktck);

	// Invalidate so destructor won't call print another log entry
	begin_time = PerfTime();
}


} // namespace noemixerr