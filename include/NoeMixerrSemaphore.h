// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2022-2022 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


/*
 * This code has been copied and adapted from https://github.com/drobilla/jalv
 * File src/zix/sem.h
 */

#ifndef NoeMixerr_SEMAPHORE_H
#define NoeMixerr_SEMAPHORE_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_BUILD_APPLE
#    include <mach/mach.h>
#elif defined(NoeMixerr_BUILD_WIN32)
#    include <windows.h>
#else
#    include <semaphore.h>
#endif


namespace noemixerr {

/**
   A counting semaphore.

   This is an integer that is always positive, and has two main operations:
   increment (post) and decrement (wait).  If a decrement can not be performed
   (i.e. the value is 0) the caller will be blocked until another thread posts
   and the operation can succeed.

   Semaphores can be created with any starting value, but typically this will
   be 0 so the semaphore can be used as a simple signal where each post
   corresponds to one wait.

   Semaphores are very efficient (much more so than a mutex/cond pair).  In
   particular, at least on Linux, post is async-signal-safe, which means it
   does not block and will not be interrupted.  If you need to signal from
   a realtime thread, this is the most appropriate primitive to use.

   @note Likely outdated with C++20's std::counting_semaphore
		 (though we have to check that this will be RT conforming on all platforms)
*/
class Semaphore
{
public:
	Semaphore(unsigned initial);
	Semaphore(const Semaphore&) = delete;
	Semaphore& operator=(const Semaphore&) = delete;
	Semaphore(Semaphore&&) = delete;
	Semaphore& operator=(Semaphore&&) = delete;
	~Semaphore();

	void post();
	void wait();
	bool tryWait();

private:
#ifdef NoeMixerr_BUILD_APPLE
	semaphore_t m_sem;
#elif defined(NoeMixerr_BUILD_WIN32)
	HANDLE m_sem;
#else
	sem_t m_sem;
#endif
};

} // namespace noemixerr

#endif // NoeMixerr_SEMAPHORE_H
