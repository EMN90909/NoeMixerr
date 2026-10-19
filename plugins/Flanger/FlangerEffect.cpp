// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "FlangerEffect.h"

#include <numbers>

#include "Engine.h"
#include "MonoDelay.h"
#include "QuadratureLfo.h"

#include "embed.h"
#include "noemixerr_math.h"
#include "plugin_export.h"

namespace noemixerr
{


extern "C"
{

Plugin::Descriptor PLUGIN_EXPORT flanger_plugin_descriptor =
{
	NoeMixerr_STRINGIFY( PLUGIN_NAME ),
	"Flanger",
	QT_TRANSLATE_NOOP( "PluginBrowser", "A native flanger plugin" ),
	"Dave French <contact/dot/dave/dot/french3/at/googlemail/dot/com>",
	0x0100,
	Plugin::Type::Effect,
	new PixmapLoader("noemixerr-plugin-logo"),
	nullptr,
	nullptr,
} ;




FlangerEffect::FlangerEffect( Model *parent, const Plugin::Descriptor::SubPluginFeatures::Key *key ) :
	Effect( &flanger_plugin_descriptor, parent, key ),
	m_flangerControls( this )
{
	m_lfo = new QuadratureLfo( Engine::audioEngine()->outputSampleRate() );
	m_lDelay = new MonoDelay( 1, Engine::audioEngine()->outputSampleRate() );
	m_rDelay = new MonoDelay( 1, Engine::audioEngine()->outputSampleRate() );
}




FlangerEffect::~FlangerEffect()
{
	if(m_lDelay )
	{
		delete m_lDelay;
	}
	if( m_rDelay )
	{
		delete m_rDelay;
	}
	if( m_lfo )
	{
		delete m_lfo;
	}
}




Effect::ProcessStatus FlangerEffect::processImpl(SampleFrame* buf, const f_cnt_t frames)
{
	const float d = dryLevel();
	const float w = wetLevel();
	const float length = m_flangerControls.m_delayTimeModel.value() * Engine::audioEngine()->outputSampleRate();
	const float noise = m_flangerControls.m_whiteNoiseAmountModel.value();
	float amplitude = m_flangerControls.m_lfoAmountModel.value() * Engine::audioEngine()->outputSampleRate();
	bool invertFeedback = m_flangerControls.m_invertFeedbackModel.value();
	m_lfo->setFrequency(  1.0/m_flangerControls.m_lfoFrequencyModel.value() );
	m_lfo->setOffset(m_flangerControls.m_lfoPhaseModel.value() / 180 * std::numbers::pi);
	m_lDelay->setFeedback( m_flangerControls.m_feedbackModel.value() );
	m_rDelay->setFeedback( m_flangerControls.m_feedbackModel.value() );
	auto dryS = std::array<sample_t, 2>{};
	for( f_cnt_t f = 0; f < frames; ++f )
	{
		float leftLfo;
		float rightLfo;

		buf[f][0] += fastRandInc(-1.f, 1.f) * noise;
		buf[f][1] += fastRandInc(-1.f, 1.f) * noise;
		dryS[0] = buf[f][0];
		dryS[1] = buf[f][1];
		m_lfo->tick(&leftLfo, &rightLfo);
		m_lDelay->setLength( ( float )length + amplitude * (leftLfo+1.0)  );
		m_rDelay->setLength( ( float )length + amplitude * (rightLfo+1.0)  );
		if(invertFeedback)
		{
			m_lDelay->tick( &buf[f][1] );
			m_rDelay->tick(&buf[f][0] );
		} else
		{
			m_lDelay->tick( &buf[f][0] );
			m_rDelay->tick( &buf[f][1] );
		}

		buf[f][0] = ( d * dryS[0] ) + ( w * buf[f][0] );
		buf[f][1] = ( d * dryS[1] ) + ( w * buf[f][1] );
	}

	return ProcessStatus::ContinueIfNotQuiet;
}




void FlangerEffect::changeSampleRate()
{
	m_lfo->setSampleRate( Engine::audioEngine()->outputSampleRate() );
	m_lDelay->setSampleRate( Engine::audioEngine()->outputSampleRate() );
	m_rDelay->setSampleRate( Engine::audioEngine()->outputSampleRate() );
}




void FlangerEffect::restartLFO()
{
	m_lfo->restart();
}




extern "C"
{

//needed for getting plugin out of shared lib
PLUGIN_EXPORT Plugin * noemixerr_plugin_main( Model* parent, void* data )
{
	return new FlangerEffect( parent , static_cast<const Plugin::Descriptor::SubPluginFeatures::Key *>( data ) );
}

}}


} // namespace noemixerr
