// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_QUADRATURE_LFO_H
#define NoeMixerr_QUADRATURE_LFO_H

#include <numbers>
#include <cmath>

namespace noemixerr
{


class QuadratureLfo
{
public:
	QuadratureLfo( int sampleRate ) :
		m_frequency(0),
		m_phase(0),
		m_offset(std::numbers::pi * 0.5)
	{
		setSampleRate(sampleRate);
	}

	~QuadratureLfo() = default;

	inline void setFrequency( double frequency )
	{
		if( frequency < 0 || frequency > m_samplerate / 2.0 || frequency == m_frequency )
		{
			return;
		}
		m_frequency = frequency;
		m_increment = m_frequency * m_twoPiOverSr;
	}


	inline void restart()
	{
		m_phase = 0;
	}


	inline void setSampleRate ( int samplerate )
	{
		m_samplerate = samplerate;
		m_twoPiOverSr = 2 * std::numbers::pi_v<float> / samplerate;
		m_increment = m_frequency * m_twoPiOverSr;
	}


	inline void setOffset( double offsetVal )
	{
		m_offset = offsetVal;
	}


	void tick( float *l, float *r )
	{
		*l = std::sin(m_phase);
		*r = std::sin(m_phase + m_offset);
		m_phase += m_increment;
		m_phase = std::fmod(m_phase, 2 * std::numbers::pi);
	}

private:
	double m_frequency;
	double m_phase;
	double m_increment;
	double m_twoPiOverSr;
	double m_offset;
	int m_samplerate;

};


} // namespace noemixerr

#endif // NoeMixerr_QUADRATURE_LFO_H
