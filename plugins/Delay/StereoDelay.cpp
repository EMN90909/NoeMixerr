// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "StereoDelay.h"

#include "SampleFrame.h"

namespace noemixerr
{


StereoDelay::StereoDelay( int maxTime, int sampleRate )
{
	m_buffer = 0;
	m_maxTime = static_cast<float>(maxTime);
	m_maxLength = maxTime * sampleRate;
	m_length = static_cast<float>(m_maxLength);

	m_writeIndex = 0;
	m_feedback = 0.0f;
	setSampleRate( sampleRate );
}




StereoDelay::~StereoDelay()
{
	if( m_buffer )
	{
		delete[] m_buffer;
	}
}




void StereoDelay::tick( SampleFrame& frame )
{
	m_writeIndex = ( m_writeIndex + 1 ) % ( int )m_maxLength;
	int readIndex = m_writeIndex - static_cast<int>(m_length);
	if (readIndex < 0 ) { readIndex += m_maxLength; }
	float lOut = m_buffer[ readIndex ][ 0 ];
	float rOut = m_buffer[ readIndex ] [1 ];
	m_buffer[ m_writeIndex ][ 0 ] = frame[ 0 ] + ( lOut * m_feedback );
	m_buffer[ m_writeIndex ][ 1 ] = frame[ 1 ] + ( rOut * m_feedback );
	frame[ 0 ] = lOut;
	frame[ 1 ] = rOut;
}






void StereoDelay::setSampleRate( int sampleRate )
{
	if( m_buffer )
	{
		delete[] m_buffer;
	}

	int bufferSize = ( int )( sampleRate * m_maxTime );
	m_buffer = new SampleFrame[bufferSize];
	for( int i = 0 ; i < bufferSize ; i++)
	{
		m_buffer[i][0] = 0.0;
		m_buffer[i][1] = 0.0;
	}
}


} // namespace noemixerr
