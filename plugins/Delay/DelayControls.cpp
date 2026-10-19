// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "DelayControls.h"
#include "DelayEffect.h"
#include "Engine.h"

namespace noemixerr
{

DelayControls::DelayControls( DelayEffect* effect ):
	EffectControls( effect ),
	m_effect ( effect ),
	m_delayTimeModel(0.5f, 0.01f, 5.f, 0.0001f, 5000.f, this, tr("Delay samples")) ,
	m_feedbackModel(0.0f, 0.0f, 1.0f, 0.01f, this, tr("Feedback")),
	m_lfoTimeModel(2.f, 0.01f, 5.f, 0.0001f, 20000.f, this, tr("LFO frequency")),
	m_lfoAmountModel(0.f, 0.f, 0.5f, 0.0001f, 2000.f, this, tr("LFO amount")),
	m_outGainModel(0.f, -60.f, 20.f, 0.01f, this, tr("Output gain"))
{
	connect( Engine::audioEngine(), SIGNAL( sampleRateChanged() ), this, SLOT( changeSampleRate() ) );
	m_outPeakL = 0.0;
	m_outPeakR = 0.0;
}




void DelayControls::loadSettings( const QDomElement &_this )
{
	m_delayTimeModel.loadSettings(_this, "DelayTimeSamples" );
	m_feedbackModel.loadSettings( _this, "FeebackAmount" );
	m_lfoTimeModel.loadSettings( _this , "LfoFrequency");
	m_lfoAmountModel.loadSettings( _this, "LfoAmount");
	m_outGainModel.loadSettings( _this, "OutGain" );
}




void DelayControls::saveSettings( QDomDocument& doc, QDomElement& _this )
{
	m_delayTimeModel.saveSettings( doc, _this, "DelayTimeSamples" );
	m_feedbackModel.saveSettings( doc, _this ,"FeebackAmount" );
	m_lfoTimeModel.saveSettings( doc, _this, "LfoFrequency" );
	m_lfoAmountModel.saveSettings( doc, _this ,"LfoAmount" );
	m_outGainModel.saveSettings( doc, _this, "OutGain" );
}



void DelayControls::changeSampleRate()
{
	m_effect->changeSampleRate();
}


} // namespace noemixerr
