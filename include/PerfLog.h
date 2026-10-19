// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017-2018 LMMS Developers
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PERFLOG_H
#define NoeMixerr_PERFLOG_H

#include <ctime>
#include <QString>

namespace noemixerr
{


/// \brief CPU time point
///
/// Represents a point in CPU time (not wall-clock time) intended for measuring
/// performance.
class PerfTime
{
public:
	PerfTime();
	bool valid() const;

	clock_t real() const;
	clock_t user() const;
	clock_t system() const;

	static PerfTime now();
	static clock_t ticksPerSecond();

	friend PerfTime operator-(const PerfTime& lhs, const PerfTime& rhs);
private:
	clock_t m_real;
	clock_t m_user;
	clock_t m_system;
};

/// \brief The PerfLog class
///
/// Measures time between construction and destruction and prints the result to
/// stderr, along with \p name. Alternatively, call begin() and end() explicitly.
class PerfLogTimer
{
 public:
	PerfLogTimer(const QString& name);
	~PerfLogTimer();

	void begin();
	void end();

 private:
	QString name;
	PerfTime begin_time;
};


} // namespace noemixerr

#endif // NoeMixerr_PERFLOG_H
