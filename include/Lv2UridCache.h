// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020-2020 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LV2_URID_CACHE_H
#define NoeMixerr_LV2_URID_CACHE_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_LV2

#include <cstdint>


namespace noemixerr
{


//! Cached URIDs for fast access (for use in real-time code)
class Lv2UridCache
{
public:
	enum class Id //!< ID for m_uridCache array
	{
		// keep it alphabetically (except "size" at the end)
		atom_Float,
		atom_Int,
		bufsz_minBlockLength,
		bufsz_maxBlockLength,
		bufsz_nominalBlockLength,
		bufsz_sequenceSize,
		midi_MidiEvent,
		param_sampleRate,
		// exception to alphabetic ordering - keep at the end:
		size
	};

	template<typename T>
	struct IdForType;

	//! Return URID for a cache ID
	uint32_t operator[](Id id) const;

	Lv2UridCache(class UridMap& mapper);

private:
	uint32_t m_cache[static_cast<int>(Id::size)];
};

template<> struct Lv2UridCache::IdForType<float> { static constexpr auto value = Id::atom_Float; };
template<> struct Lv2UridCache::IdForType<std::int32_t> { static constexpr auto value = Id::atom_Int; };


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

#endif // NoeMixerr_LV2_URID_CACHE_H
