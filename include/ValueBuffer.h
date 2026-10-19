// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_VALUE_BUFFER_H
#define NoeMixerr_VALUE_BUFFER_H

#include <vector>

#include "noemixerr_export.h"

namespace noemixerr
{


class NoeMixerr_EXPORT ValueBuffer : public std::vector<float>
{
public:
	ValueBuffer() = default;
	ValueBuffer(int length);

	void fill(float value);

	float value(int offset ) const;

	const float * values() const;
	float * values();
	
	int length() const;

	void interpolate(float start, float end);
};


} // namespace noemixerr

#endif // NoeMixerr_VALUE_BUFFER_H
