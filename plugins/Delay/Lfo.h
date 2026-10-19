// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LFO_H
#define LFO_H

#include <cmath>
#include <numbers>

namespace noemixerr
{


class Lfo
{
public:
	Lfo( int samplerate );
	~Lfo() = default;




	inline void setFrequency( double frequency )
	{
		if( frequency < 0 || frequency > ( m_samplerate / 2.0 ) || frequency == m_frequency )
		{
			return;
		}
		m_frequency = frequency;
		m_increment = m_frequency * m_twoPiOverSr;

		m_phase = std::fmod(m_phase, 2 * std::numbers::pi_v<float>);
	}




	inline void setSampleRate ( int samplerate )
	{
		m_samplerate = samplerate;
		m_twoPiOverSr = 2 * std::numbers::pi_v<float> / samplerate;
		m_increment = m_frequency * m_twoPiOverSr;
	}




	float tick();

private:
	double m_frequency;
	double m_phase;
	double m_increment;
	double m_twoPiOverSr;
	int m_samplerate;
};


} // namespace noemixerr

#endif // LFO_H
