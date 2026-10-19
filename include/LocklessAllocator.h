// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2016 Javier Serrano Polo <javier@jasp.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LOCKLESS_ALLOCATOR_H
#define NoeMixerr_LOCKLESS_ALLOCATOR_H

#include <atomic>
#include <cstddef>


namespace noemixerr
{


class LocklessAllocator
{
public:
	LocklessAllocator( size_t nmemb, size_t size );
	virtual ~LocklessAllocator();
	void * alloc();
	void free( void * ptr );


private:
	char * m_pool;
	size_t m_capacity;
	size_t m_elementSize;

	std::atomic_int * m_freeState;
	size_t m_freeStateSets;

	std::atomic_size_t m_available;
	std::atomic_size_t m_startIndex;

} ;




template<typename T>
class LocklessAllocatorT : private LocklessAllocator
{
public:
	LocklessAllocatorT( size_t nmemb ) :
		LocklessAllocator( nmemb, sizeof( T ) )
	{
	}

	~LocklessAllocatorT() override = default;

	T * alloc()
	{
		return (T *)LocklessAllocator::alloc();
	}

	void free( T * ptr )
	{
		LocklessAllocator::free( ptr );
	}

} ;


} // namespace noemixerr

#endif // NoeMixerr_LOCKLESS_ALLOCATOR_H
