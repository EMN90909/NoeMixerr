// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "DelayEffect.h"
#include "Engine.h"
#include "embed.h"
#include "Lfo.h"
#include "noemixerr_math.h"
#include "plugin_export.h"
#include "StereoDelay.h"

namespace noemixerr
{


extern "C"
{

Plugin::Descriptor PLUGIN_EXPORT delay_plugin_descriptor =
{
	NoeMixerr_STRINGIFY( PLUGIN_NAME ),
	"Delay",
	QT_TRANSLATE_NOOP( "PluginBrowser", "A native delay plugin" ),
	"Dave French <contact/dot/dave/dot/french3/at/googlemail/dot/com>",
	0x0100,
	Plugin::Type::Effect,
	new PixmapLoader("noemixerr-plugin-logo"),
	nullptr,
	nullptr,
} ;




DelayEffect::DelayEffect( Model* parent, const Plugin::Descriptor::SubPluginFeatures::Key* key ) :
	Effect( &delay_plugin_descriptor, parent, key ),
	m_delayControls( this )
{
	m_delay = 0;
	m_delay = new StereoDelay( 20, Engine::audioEngine()->outputSampleRate() );
	m_lfo = new Lfo( Engine::audioEngine()->outputSampleRate() );
	m_outGain = 1.0;
}




DelayEffect::~DelayEffect()
{
	if( m_delay )
	{
		delete m_delay;
	}
	if( m_lfo )
	{
		delete m_lfo;
	}
}




Effect::ProcessStatus DelayEffect::processImpl(SampleFrame* buf, const f_cnt_t frames)
{
	const float sr = Engine::audioEngine()->outputSampleRate();
	const float d = dryLevel();
	const float w = wetLevel();

	SampleFrame peak;
	float length = m_delayControls.m_delayTimeModel.value();
	float amplitude = m_delayControls.m_lfoAmountModel.value() * sr;
	float lfoTime = 1.0 / m_delayControls.m_lfoTimeModel.value();
	float feedback =  m_delayControls.m_feedbackModel.value();
	ValueBuffer *lengthBuffer = m_delayControls.m_delayTimeModel.valueBuffer();
	ValueBuffer *feedbackBuffer = m_delayControls.m_feedbackModel.valueBuffer();
	ValueBuffer *lfoTimeBuffer = m_delayControls.m_lfoTimeModel.valueBuffer();
	ValueBuffer *lfoAmountBuffer = m_delayControls.m_lfoAmountModel.valueBuffer();
	int lengthInc = lengthBuffer ? 1 : 0;
	int amplitudeInc = lfoAmountBuffer ? 1 : 0;
	int lfoTimeInc = lfoTimeBuffer ? 1 : 0;
	int feedbackInc = feedbackBuffer ? 1 : 0;
	float *lengthPtr = lengthBuffer ? &( lengthBuffer->values()[ 0 ] ) : &length;
	float *amplitudePtr = lfoAmountBuffer ? &( lfoAmountBuffer->values()[ 0 ] ) : &amplitude;
	float *lfoTimePtr = lfoTimeBuffer ? &( lfoTimeBuffer->values()[ 0 ] ) : &lfoTime;
	float *feedbackPtr = feedbackBuffer ? &( feedbackBuffer->values()[ 0 ] ) : &feedback;

	if( m_delayControls.m_outGainModel.isValueChanged() )
	{
		m_outGain = dbfsToAmp( m_delayControls.m_outGainModel.value() );
	}

	for (f_cnt_t f = 0; f < frames; ++f)
	{
		auto& currentFrame = buf[f];
		const auto dryS = currentFrame;

		// Prepare delay for current sample
		m_delay->setFeedback( *feedbackPtr );
		m_lfo->setFrequency( *lfoTimePtr );
		m_currentLength = static_cast<int>(*lengthPtr * Engine::audioEngine()->outputSampleRate());
		m_delay->setLength( m_currentLength + ( *amplitudePtr * ( float )m_lfo->tick() ) );

		// Process the wet signal
		m_delay->tick( currentFrame );
		currentFrame *= m_outGain;

		// Calculate peak of wet signal
		peak = peak.absMax(currentFrame);

		// Dry/wet mix
		currentFrame = dryS * d + currentFrame * w;

		lengthPtr += lengthInc;
		amplitudePtr += amplitudeInc;
		lfoTimePtr += lfoTimeInc;
		feedbackPtr += feedbackInc;
	}

	m_delayControls.m_outPeakL = peak.left();
	m_delayControls.m_outPeakR = peak.right();

	return ProcessStatus::ContinueIfNotQuiet;
}

void DelayEffect::changeSampleRate()
{
	m_lfo->setSampleRate( Engine::audioEngine()->outputSampleRate() );
	m_delay->setSampleRate( Engine::audioEngine()->outputSampleRate() );
}




extern "C"
{

//needed for getting plugin out of shared lib
PLUGIN_EXPORT Plugin * noemixerr_plugin_main( Model* parent, void* data )
{
	return new DelayEffect( parent , static_cast<const Plugin::Descriptor::SubPluginFeatures::Key *>( data ) );
}

}}


} // namespace noemixerr
