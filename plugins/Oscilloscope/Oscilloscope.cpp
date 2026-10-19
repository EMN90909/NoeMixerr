// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Keratin
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Oscilloscope.h"

#include "embed.h"
#include "plugin_export.h"

namespace noemixerr
{

extern "C"
{
Plugin::Descriptor PLUGIN_EXPORT oscilloscope_plugin_descriptor =
{
	NoeMixerr_STRINGIFY(PLUGIN_NAME),
	"Oscilloscope",
	QT_TRANSLATE_NOOP("PluginBrowser", "Oscilloscope plugin to display the incoming audio waveform"),
	"Keratin <3",
	0x0100,
	Plugin::Type::Effect,
	new PixmapLoader("noemixerr-plugin-logo"),
	nullptr,
	nullptr,
};

PLUGIN_EXPORT Plugin* noemixerr_plugin_main(Model* parent, void* data)
{
	return new Oscilloscope(parent, static_cast<const Plugin::Descriptor::SubPluginFeatures::Key*>(data));
}
}


Oscilloscope::Oscilloscope(Model* parent, const Descriptor::SubPluginFeatures::Key* key) :
	Effect(&oscilloscope_plugin_descriptor, parent, key),
	m_controls(this),
	m_inputBuffer(InputBufferSize)
{
}


Effect::ProcessStatus Oscilloscope::processImpl(SampleFrame* buffer, const f_cnt_t frames)
{
	if (!m_controls.m_pauseModel.value())
	{
		// Send the samples from the audio thread over to the gui via a ring buffer; the gui will do all of the processing.
		m_inputBuffer.write(buffer, frames);
	}
	return ProcessStatus::Continue;
}



} // namespace noemixerr
