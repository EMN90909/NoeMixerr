// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Lfo.h"

#include <cmath>
#include <numbers>

namespace noemixerr
{


Lfo::Lfo( int samplerate )
{
	m_samplerate = samplerate;
	m_twoPiOverSr = 2 * std::numbers::pi_v<float> / samplerate;
}




float Lfo::tick()
{
	float output = std::sin(m_phase);
	m_phase += m_increment;

	return output;
}


} // namespace noemixerr
