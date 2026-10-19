// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020-2020 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LV2_FEATURES_H
#define NoeMixerr_LV2_FEATURES_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_LV2

#include <map>
#include <string_view>
#include <vector>

#include <lv2/core/lv2.h>

namespace noemixerr
{

/**
	Feature container

	References all available features for a plugin and maps them to their URIs.

	The public member functions should be called in descending order:

	1. initCommon: map plugin-common features
	2. operator[]: map plugin-specific features
	3. createFeatureVectors: create the feature vectors required for
		lilv_plugin_instantiate
	4. access the latter
*/
class Lv2Features
{
public:
	//! Return if a feature is supported by NoeMixerr
	static bool isFeatureSupported(const char *featName);

	Lv2Features();

	//! Register only plugin-common features
	void initCommon();
	//! Return reference to feature data with given URI featName
	void*& operator[](const char* featName);
	//! Fill m_features and m_featurePointers with all features
	void createFeatureVectors();
	//! Return LV2_Feature pointer vector, suited for lilv_plugin_instantiate
	const LV2_Feature* const* featurePointers() const
	{
		return m_featurePointers.data();
	}
	//! Clear everything
	void clear();

private:
	//! feature storage
	std::vector<LV2_Feature> m_features;
	//! pointers to m_features, required for lilv_plugin_instantiate
	std::vector<const LV2_Feature*> m_featurePointers;
	//! features + data, ordered by URI
	std::map<std::string_view, void*> m_featureByUri;
};


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

#endif // NoeMixerr_LV2_FEATURES_H
