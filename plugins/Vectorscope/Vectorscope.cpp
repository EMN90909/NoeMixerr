// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Vectorscope.h"

#include "embed.h"
#include "plugin_export.h"

namespace noemixerr
{


extern "C" {
	Plugin::Descriptor PLUGIN_EXPORT vectorscope_plugin_descriptor =
	{
		NoeMixerr_STRINGIFY(PLUGIN_NAME),
		"Vectorscope",
		QT_TRANSLATE_NOOP("PluginBrowser", "A stereo field visualizer."),
		"Martin Pavelek <he29/dot/HS/at/gmail/dot/com>",
		0x0100,
		Plugin::Type::Effect,
		new PixmapLoader("noemixerr-plugin-logo"),
		nullptr,
		nullptr,
	};
}


Vectorscope::Vectorscope(Model *parent, const Plugin::Descriptor::SubPluginFeatures::Key *key) :
	Effect(&vectorscope_plugin_descriptor, parent, key),
	m_controls(this),
	// Buffer is sized to cover 4* the current maximum NoeMixerr audio buffer size,
	// so that it has some reserve space in case GUI thresd is busy.
	m_inputBuffer(4 * m_maxBufferSize)
{
}


// Take audio data and store them for processing and display in the GUI thread.
Effect::ProcessStatus Vectorscope::processImpl(SampleFrame* buf, const f_cnt_t frames)
{
	// Skip processing if the controls dialog isn't visible, it would only waste CPU cycles.
	if (m_controls.isViewVisible())
	{
		// To avoid processing spikes on audio thread, data are stored in
		// a lockless ringbuffer and processed in a separate thread.
		m_inputBuffer.write(buf, frames);
	}

	return ProcessStatus::Continue;
}


extern "C" {
	// needed for getting plugin out of shared lib
	PLUGIN_EXPORT Plugin *noemixerr_plugin_main(Model *parent, void *data)
	{
		return new Vectorscope(parent, static_cast<const Plugin::Descriptor::SubPluginFeatures::Key *>(data));
	}
}


} // namespace noemixerr
