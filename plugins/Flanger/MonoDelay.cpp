// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "MonoDelay.h"
#include "string.h"

namespace noemixerr
{


MonoDelay::MonoDelay( int maxTime , int sampleRate )
{
	m_buffer = 0;
	m_maxTime = static_cast<float>(maxTime);
	m_maxLength = maxTime * sampleRate;
	m_length = static_cast<float>(m_maxLength);

	m_writeIndex = 0;
	m_feedback = 0.0f;
	setSampleRate( sampleRate );
}




MonoDelay::~MonoDelay()
{
	if( m_buffer )
	{
		delete m_buffer;
	}
}



void MonoDelay::tick( sample_t* sample )
{
	m_writeIndex = ( m_writeIndex + 1 ) % ( int )m_maxLength;
	int readIndex = m_writeIndex - static_cast<int>(m_length);
	if (readIndex < 0 ) { readIndex += m_maxLength; }
	float out = m_buffer[ readIndex ];
	m_buffer[ m_writeIndex ] = *sample + ( out * m_feedback );
	*sample = out;
}




void MonoDelay::setSampleRate( int sampleRate )
{
	if( m_buffer )
	{
		delete m_buffer;
	}


	m_buffer = new sample_t[( int )( sampleRate * m_maxTime ) ];
	memset( m_buffer, 0, sizeof(float) * ( int )( sampleRate * m_maxTime ) );
}


} // namespace noemixerr
