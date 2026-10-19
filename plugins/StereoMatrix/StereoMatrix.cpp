// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "StereoMatrix.h"

#include "embed.h"
#include "plugin_export.h"

namespace noemixerr
{


extern "C"
{

Plugin::Descriptor PLUGIN_EXPORT stereomatrix_plugin_descriptor =
{
	NoeMixerr_STRINGIFY( PLUGIN_NAME ),
	"Stereo Matrix",
	QT_TRANSLATE_NOOP( "PluginBrowser",
				"Plugin for freely manipulating stereo output" ),
	"Paul Giblock <drfaygo/at/gmail.com>",
	0x0100,
	Plugin::Type::Effect,
	new PixmapLoader("noemixerr-plugin-logo"),
	nullptr,
	nullptr,
} ;

}



StereoMatrixEffect::StereoMatrixEffect(
			Model * _parent,
			const Descriptor::SubPluginFeatures::Key * _key ) :
	Effect( &stereomatrix_plugin_descriptor, _parent, _key ),
	m_smControls( this )
{
}




Effect::ProcessStatus StereoMatrixEffect::processImpl(SampleFrame* buf, const f_cnt_t frames)
{
	for (f_cnt_t f = 0; f < frames; ++f)
	{	
		const float d = dryLevel();
		const float w = wetLevel();
		
		sample_t l = buf[f][0];
		sample_t r = buf[f][1];

		// Init with dry-mix
		buf[f][0] = l * d;
		buf[f][1] = r * d;

		// Add it wet
		buf[f][0] += ( m_smControls.m_llModel.value( f ) * l  +
					m_smControls.m_rlModel.value( f ) * r ) * w;

		buf[f][1] += ( m_smControls.m_lrModel.value( f ) * l  +
					m_smControls.m_rrModel.value( f ) * r ) * w;
	}

	return ProcessStatus::ContinueIfNotQuiet;
}




extern "C"
{

// necessary for getting instance out of shared lib
PLUGIN_EXPORT Plugin * noemixerr_plugin_main( Model * _parent, void * _data )
{
	return( new StereoMatrixEffect( _parent,
		static_cast<const Plugin::Descriptor::SubPluginFeatures::Key *>(
								_data ) ) );
}

}


} // namespace noemixerr
