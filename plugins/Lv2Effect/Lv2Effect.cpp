// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Lv2Effect.h"

#include <QDebug>

#include "Lv2SubPluginFeatures.h"

#include "embed.h"
#include "plugin_export.h"


namespace noemixerr
{


extern "C"
{

Plugin::Descriptor PLUGIN_EXPORT lv2effect_plugin_descriptor =
{
	NoeMixerr_STRINGIFY(PLUGIN_NAME),
	"LV2",
	QT_TRANSLATE_NOOP("PluginBrowser",
		"plugin for using arbitrary LV2-effects inside NoeMixerr."),
	"Johannes Lorenz <jlsf2013$$$users.sourceforge.net, $$$=@>",
	0x0100,
	Plugin::Type::Effect,
	new PluginPixmapLoader("logo"),
	nullptr,
	new Lv2SubPluginFeatures(Plugin::Type::Effect)
};

}




Lv2Effect::Lv2Effect(Model* parent, const Descriptor::SubPluginFeatures::Key *key) :
	Effect(&lv2effect_plugin_descriptor, parent, key),
	m_controls(this, key->attributes["uri"]),
	m_tmpOutputSmps(Engine::audioEngine()->framesPerPeriod())
{
}




Effect::ProcessStatus Lv2Effect::processImpl(SampleFrame* buf, const f_cnt_t frames)
{
	Q_ASSERT(frames <= static_cast<f_cnt_t>(m_tmpOutputSmps.size()));

	m_controls.copyBuffersFromNoeMixerr(buf, frames);
	m_controls.copyModelsFromNoeMixerr();

//	m_pluginMutex.lock();
	m_controls.run(frames);
//	m_pluginMutex.unlock();

	m_controls.copyModelsToNoeMixerr();
	m_controls.copyBuffersToNoeMixerr(m_tmpOutputSmps.data(), frames);

	bool corrupt = wetLevel() < 0; // #3261 - if w < 0, bash w := 0, d := 1
	const float d = corrupt ? 1 : dryLevel();
	const float w = corrupt ? 0 : wetLevel();
	for(f_cnt_t f = 0; f < frames; ++f)
	{
		buf[f][0] = d * buf[f][0] + w * m_tmpOutputSmps[f][0];
		buf[f][1] = d * buf[f][1] + w * m_tmpOutputSmps[f][1];
	}

	return ProcessStatus::ContinueIfNotQuiet;
}




extern "C"
{

// necessary for getting instance out of shared lib
PLUGIN_EXPORT Plugin *noemixerr_plugin_main(Model *_parent, void *_data)
{
	using KeyType = Plugin::Descriptor::SubPluginFeatures::Key;
	try {
		return new Lv2Effect(_parent, static_cast<const KeyType*>(_data));
	} catch (const std::runtime_error& e) {
		qCritical() << e.what();
		return nullptr;
	}
}

}


} // namespace noemixerr
