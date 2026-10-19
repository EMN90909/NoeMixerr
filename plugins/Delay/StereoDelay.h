// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef STEREODELAY_H
#define STEREODELAY_H



namespace noemixerr
{

class SampleFrame;

class StereoDelay
{
public:
	StereoDelay( int maxLength, int sampleRate );
	~StereoDelay();
	inline void setLength( float length )
	{
		if( length <= m_maxLength && length >= 0 )
		{
			m_length = length;
		}
	}

	inline void setFeedback( float feedback )
	{
		m_feedback = feedback;
	}

	void tick( SampleFrame& frame );
	void setSampleRate( int sampleRate );

private:
	SampleFrame* m_buffer;
	int m_maxLength;
	float m_length;
	int m_writeIndex;
	float m_feedback;
	float m_maxTime;
};


} // namespace noemixerr

#endif // STEREODELAY_H
