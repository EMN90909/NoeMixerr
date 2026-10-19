// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Amplifier.h"

#include "embed.h"
#include "plugin_export.h"

namespace noemixerr
{

extern "C"
{

Plugin::Descriptor PLUGIN_EXPORT amplifier_plugin_descriptor =
{
	NoeMixerr_STRINGIFY(PLUGIN_NAME),
	"Amplifier",
	QT_TRANSLATE_NOOP("PluginBrowser", "A native amplifier plugin"),
	"Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>",
	0x0100,
	Plugin::Type::Effect,
	new PixmapLoader("noemixerr-plugin-logo"),
	nullptr,
	nullptr,
} ;

}


AmplifierEffect::AmplifierEffect(Model* parent, const Descriptor::SubPluginFeatures::Key* key) :
	Effect(&amplifier_plugin_descriptor, parent, key),
	m_ampControls(this)
{
}


Effect::ProcessStatus AmplifierEffect::processImpl(SampleFrame* buf, const f_cnt_t frames)
{
	const float d = dryLevel();
	const float w = wetLevel();

	const ValueBuffer* volumeBuf = m_ampControls.m_volumeModel.valueBuffer();
	const ValueBuffer* panBuf = m_ampControls.m_panModel.valueBuffer();
	const ValueBuffer* leftBuf = m_ampControls.m_leftModel.valueBuffer();
	const ValueBuffer* rightBuf = m_ampControls.m_rightModel.valueBuffer();

	for (f_cnt_t f = 0; f < frames; ++f)
	{
		const float volume = (volumeBuf ? volumeBuf->value(f) : m_ampControls.m_volumeModel.value()) * 0.01f;
		const float pan = (panBuf ? panBuf->value(f) : m_ampControls.m_panModel.value()) * 0.01f;
		const float left = (leftBuf ? leftBuf->value(f) : m_ampControls.m_leftModel.value()) * 0.01f;
		const float right = (rightBuf ? rightBuf->value(f) : m_ampControls.m_rightModel.value()) * 0.01f;

		const float panLeft = std::min(1.0f, 1.0f - pan);
		const float panRight = std::min(1.0f, 1.0f + pan);

		auto& currentFrame = buf[f];

		const auto s = currentFrame * SampleFrame(left * panLeft, right * panRight) * volume;

		// Dry/wet mix
		currentFrame = currentFrame * d + s * w;
	}

	return ProcessStatus::ContinueIfNotQuiet;
}


extern "C"
{

// necessary for getting instance out of shared lib
PLUGIN_EXPORT Plugin* noemixerr_plugin_main(Model* parent, void* data)
{
	return new AmplifierEffect(parent, static_cast<const Plugin::Descriptor::SubPluginFeatures::Key*>(data));
}

}

} // namespace noemixerr
