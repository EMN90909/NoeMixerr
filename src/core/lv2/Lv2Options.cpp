// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020-2020 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Lv2Options.h"

#ifdef NoeMixerr_HAVE_LV2

#include <QtGlobal>


namespace noemixerr
{


std::set<LV2_URID> Lv2Options::s_supportedOptions;




bool Lv2Options::isOptionSupported(LV2_URID key)
{
	return s_supportedOptions.find(key) != s_supportedOptions.end();
}




void Lv2Options::supportOption(LV2_URID key)
{
	const auto result = s_supportedOptions.insert(key);
	Q_ASSERT(result.second);
}




void Lv2Options::createOptionVectors()
{
	// create vector of options
	for(LV2_URID urid : s_supportedOptions)
	{
		auto itr = m_optionByUrid.find(urid);
		Q_ASSERT(itr != m_optionByUrid.end());
		m_options.push_back(itr->second);
	}
	LV2_Options_Option nullOption;
	nullOption.key = 0;
	nullOption.value = nullptr;
	m_options.push_back(nullOption);
}




void Lv2Options::initOption(LV2_URID key, uint32_t size, LV2_URID type,
	std::shared_ptr<void> value,
	LV2_Options_Context context, uint32_t subject)
{
	Q_ASSERT(isOptionSupported(key));

	LV2_Options_Option opt;
	opt.key = key;
	opt.context = context;
	opt.subject = subject;
	opt.size = size;
	opt.type = type;
	opt.value = value.get();

	const auto optResult = m_optionByUrid.emplace(key, opt);
	const auto valResult = m_optionValues.emplace(key, std::move(value));
	Q_ASSERT(optResult.second);
	Q_ASSERT(valResult.second);
}




void Lv2Options::clear()
{
	m_options.clear();
	m_optionValues.clear();
	m_optionByUrid.clear();
}


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2
