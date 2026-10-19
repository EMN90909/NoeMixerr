// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020-2020 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LV2_OPTIONS_H
#define NoeMixerr_LV2_OPTIONS_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_LV2

#include <cstdint>
#include <lv2/options/options.h>
#include <lv2/urid/urid.h>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "Engine.h"
#include "Lv2Manager.h"
#include "Lv2UridCache.h"

namespace noemixerr
{

/**
	Option container

	References all available options for a plugin and maps them to their URIDs.
	This class is used per Lv2 processor (justification in Lv2Proc::initMOptions())

	The public member functions should be called in descending order:

	1. supportOption: set all supported option URIDs
	2. initOption: initialize options with values
	3. createOptionVectors: create the option vectors required for
		the feature
	4. access the latter using feature()
*/
class Lv2Options
{
public:
	//! Return if an option is supported by NoeMixerr
	static bool isOptionSupported(LV2_URID key);
	//! Mark option as supported
	static void supportOption(LV2_URID key);

	//! Initialize an option
	template<typename Opt, typename Arg>
	void initOption(Lv2UridCache::Id key, Arg&& value,
			LV2_Options_Context context = LV2_OPTIONS_INSTANCE,
			std::uint32_t subject = 0)
	{
		const Lv2UridCache& cache = Engine::getLv2Manager()->uridCache();
		initOption(cache[key], sizeof(Opt), cache[Lv2UridCache::IdForType<Opt>::value],
			std::make_shared<Opt>(std::forward<Arg>(value)), context, subject);
	}
	//! Fill m_options and m_optionPointers with all options
	void createOptionVectors();
	//! Return the feature
	const LV2_Options_Option* feature() const
	{
		return m_options.data();
	}

	void clear();

private:
	//! Initialize an option internally
	void initOption(LV2_URID key,
		uint32_t size,
		LV2_URID type,
		std::shared_ptr<void> value,
		LV2_Options_Context context = LV2_OPTIONS_INSTANCE,
		uint32_t subject = 0);
	//! options that are supported by every processor
	static std::set<LV2_URID> s_supportedOptions;
	//! options + data, ordered by URID
	std::map<LV2_URID, LV2_Options_Option> m_optionByUrid;
	//! option storage
	std::vector<LV2_Options_Option> m_options;
	//! option value storage
	std::map<LV2_URID, std::shared_ptr<void>> m_optionValues;
};


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

#endif // NoeMixerr_LV2_OPTIONS_H
