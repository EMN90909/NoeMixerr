// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Johannes Lorenz <j.git$$$lorenz-ho.me, $$$=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LV2_URID_MAP_H
#define NoeMixerr_LV2_URID_MAP_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_LV2

#include <lv2/urid/urid.h>
#include <mutex> // TODO: use semaphore, even though this is not realtime critical
#include <string>
#include <unordered_map>
#include <vector>


namespace noemixerr
{


/**
 * Complete implementation of the Lv2 Urid Map extension
 */
class UridMap
{
	std::unordered_map<std::string, LV2_URID> m_map;
	std::vector<const char*> m_unMap;

	//! mutex for both m_map and m_unMap
	//! the URID map is global, which is why a mutex is required here
	std::mutex m_MapMutex;

	LV2_URID_Map m_mapFeature;
	LV2_URID_Unmap m_unmapFeature;

public:
	//! constructor; will set up the features
	UridMap();

	//! map feature function
	LV2_URID map(const char* uri);
	//! unmap feature function
	const char* unmap(LV2_URID urid);

	// access the features
	LV2_URID_Map* mapFeature() { return &m_mapFeature; }
	LV2_URID_Unmap* unmapFeature() { return &m_unmapFeature; }
};


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

#endif // NoeMixerr_LV2_URID_MAP_H
