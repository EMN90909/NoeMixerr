// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020-2020 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Lv2Features.h"

#ifdef NoeMixerr_HAVE_LV2

#include <QtGlobal>

#include "Engine.h"
#include "Lv2Manager.h"


namespace noemixerr
{


bool Lv2Features::isFeatureSupported(const char* featName)
{
	return Engine::getLv2Manager()->isFeatureSupported(featName);
}




Lv2Features::Lv2Features()
{
	const Lv2Manager* man = Engine::getLv2Manager();
	// create (yet empty) map feature URI -> feature
	for(auto uri : man->supportedFeatureURIs())
	{
		m_featureByUri.emplace(uri, nullptr);
	}
}




void Lv2Features::initCommon()
{
	Lv2Manager* man = Engine::getLv2Manager();
	// init m_featureByUri with the plugin-common features
	operator[](LV2_URID__map) = man->uridMap().mapFeature();
	operator[](LV2_URID__unmap) = man->uridMap().unmapFeature();
}




void Lv2Features::createFeatureVectors()
{
	// create vector of features
	for(const auto& [uri, feature] : m_featureByUri)
	{
		/*
			If pr.second is nullptr here, this means that the LV2_feature
			has no "data". If this happens here, this means
			* either that this feature is static
			  (e.g. LV2_BUF_SIZE__boundedBlockLength)
			* or that the programmer forgot to use operator[] before feature
			  vector creation (This can be done in
			  Lv2Proc::initPluginSpecificFeatures or in Lv2Features::initCommon)
		*/
		m_features.push_back(LV2_Feature{(const char*)uri.data(), (void*)feature});
	}

	// create pointer vector (for lilv_plugin_instantiate)
	m_featurePointers.reserve(m_features.size() + 1);
	for (const auto& feature : m_features)
	{
		m_featurePointers.push_back(&feature);
	}
	m_featurePointers.push_back(nullptr);
}




void *&Lv2Features::operator[](const char *featName)
{
	auto itr = m_featureByUri.find(featName);
	Q_ASSERT(itr != m_featureByUri.end());
	return itr->second;
}




void Lv2Features::clear()
{
	m_features.clear();
	for (auto& [uri, feature] : m_featureByUri)
	{
		(void) uri;
		feature = nullptr;
	}
}


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

