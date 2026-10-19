// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "BassBooster.h"

#include "embed.h"
#include "plugin_export.h"

namespace noemixerr
{


extern "C"
{

Plugin::Descriptor PLUGIN_EXPORT bassbooster_plugin_descriptor =
{
	NoeMixerr_STRINGIFY( PLUGIN_NAME ),
	"BassBooster",
	QT_TRANSLATE_NOOP( "PluginBrowser", "Boost your bass the fast and simple way" ),
	"Tobias Doerffel <tobydox/at/users.sf.net>",
	0x0100,
	Plugin::Type::Effect,
	new PixmapLoader("noemixerr-plugin-logo"),
	nullptr,
	nullptr,
} ;

}



BassBoosterEffect::BassBoosterEffect( Model* parent, const Descriptor::SubPluginFeatures::Key* key ) :
	Effect( &bassbooster_plugin_descriptor, parent, key ),
	m_frequencyChangeNeeded( false ),
	m_bbFX( DspEffectLibrary::FastBassBoost( 70.0f, 1.0f, 2.8f ) ),
	m_bbControls( this )
{
	changeFrequency();
	changeGain();
	changeRatio();
}








Effect::ProcessStatus BassBoosterEffect::processImpl(SampleFrame* buf, const f_cnt_t frames)
{
	// check out changed controls
	if( m_frequencyChangeNeeded || m_bbControls.m_freqModel.isValueChanged() )
	{
		changeFrequency();
		m_frequencyChangeNeeded = false;
	}
	if( m_bbControls.m_gainModel.isValueChanged() ) { changeGain(); }
	if( m_bbControls.m_ratioModel.isValueChanged() ) { changeRatio(); }

	const float const_gain = m_bbControls.m_gainModel.value();
	const ValueBuffer *gainBuffer = m_bbControls.m_gainModel.valueBuffer();

	const float d = dryLevel();
	const float w = wetLevel();

	for (f_cnt_t f = 0; f < frames; ++f)
	{
		auto& currentFrame = buf[f];

		// Process copy of current sample frame
		m_bbFX.setGain(gainBuffer ? gainBuffer->value(f) : const_gain);
		auto s = currentFrame;
		m_bbFX.nextSample(s);

		// Dry/wet mix
		currentFrame = currentFrame * d + s * w;
	}

	return ProcessStatus::ContinueIfNotQuiet;
}


inline void BassBoosterEffect::changeFrequency()
{
	const sample_t fac = Engine::audioEngine()->outputSampleRate() / 44100.0f;

	m_bbFX.leftFX().setFrequency( m_bbControls.m_freqModel.value() * fac );
	m_bbFX.rightFX().setFrequency( m_bbControls.m_freqModel.value() * fac );
}




inline void BassBoosterEffect::changeGain()
{
	m_bbFX.leftFX().setGain( m_bbControls.m_gainModel.value() );
	m_bbFX.rightFX().setGain( m_bbControls.m_gainModel.value() );
}




inline void BassBoosterEffect::changeRatio()
{
	m_bbFX.leftFX().setRatio( m_bbControls.m_ratioModel.value() );
	m_bbFX.rightFX().setRatio( m_bbControls.m_ratioModel.value() );
}




extern "C"
{

// necessary for getting instance out of shared lib
PLUGIN_EXPORT Plugin * noemixerr_plugin_main( Model* parent, void* data )
{
	return new BassBoosterEffect( parent, static_cast<const Plugin::Descriptor::SubPluginFeatures::Key *>( data ) );
}

}


} // namespace noemixerr
