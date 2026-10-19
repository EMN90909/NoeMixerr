// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_RMS_HELPER_H
#define NoeMixerr_RMS_HELPER_H

#include "noemixerr_math.h"


namespace noemixerr
{


class RmsHelper
{
public:
	RmsHelper(std::size_t size) :
		m_buffer( nullptr )
	{
		setSize( size );
	}
	virtual ~RmsHelper() 
	{
		if( m_buffer ) delete[] m_buffer;
	}

	void setSize(std::size_t size)
	{
		if( m_buffer )
		{
			if( m_size < size )
			{
				delete m_buffer;
				m_buffer = new float[ size ];
				m_size = size;
				reset();
			}
			else
			{
				m_size = size;
				reset();
			}
		}
		else
		{
			m_buffer = new float[ size ];
			m_size = size;
			reset();
		}
	}

	inline void reset()
	{
		m_sizef = 1.0f / (float) m_size;
		m_pos = 0;
		m_sum = 0.0f;
		memset( m_buffer, 0, m_size * sizeof( float ) );
	}

	inline float update( const float in )
	{
		m_sum -= m_buffer[ m_pos ];
		m_sum += m_buffer[ m_pos ] = in * in;
		++m_pos %= m_size;
		return std::sqrt(m_sum * m_sizef);
	}

private:
	float * m_buffer;
	float m_sum;
	std::size_t m_pos;
	std::size_t m_size;
	float m_sizef;
};


} // namespace noemixerr

#endif // NoeMixerr_RMS_HELPER_H
