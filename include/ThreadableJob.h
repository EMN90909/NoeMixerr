// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2009-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_THREADABLE_JOB_H
#define NoeMixerr_THREADABLE_JOB_H

#include "NoeMixerrTypes.h"

#include <atomic>

namespace noemixerr
{

class ThreadableJob
{
public:

	enum class ProcessingState : int
	{
		Unstarted,
		Queued,
		InProgress,
		Done
	};

	ThreadableJob() :
		m_state(ProcessingState::Unstarted)
	{
	}

	inline ProcessingState state() const
	{
		return m_state.load();
	}

	inline void reset()
	{
		m_state = ProcessingState::Unstarted;
	}

	inline void queue()
	{
		m_state = ProcessingState::Queued;
	}
	
	inline void done()
	{
		m_state = ProcessingState::Done;
	}

	void process()
	{
		auto expected = ProcessingState::Queued;
		if (m_state.compare_exchange_strong(expected, ProcessingState::InProgress))
		{
			doProcessing();
			m_state = ProcessingState::Done;
		}
	}

	virtual bool requiresProcessing() const = 0;


protected:
	virtual void doProcessing() = 0;

	std::atomic<ProcessingState> m_state;
} ;

} // namespace noemixerr

#endif // NoeMixerr_THREADABLE_JOB_H
