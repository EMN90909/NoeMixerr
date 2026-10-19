// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "Song.h"
#include "PresetPreviewPlayHandle.h"
#include "PeakController.h"
#include "PeakControllerEffect.h"
#include "noemixerr_math.h"

#include "embed.h"
#include "plugin_export.h"

namespace noemixerr
{


extern "C"
{

Plugin::Descriptor PLUGIN_EXPORT peakcontrollereffect_plugin_descriptor =
{
	NoeMixerr_STRINGIFY( PLUGIN_NAME ),
	"Peak Controller",
	QT_TRANSLATE_NOOP( "PluginBrowser",
			"Plugin for controlling knobs with sound peaks" ),
	"Paul Giblock <drfaygo/at/gmail.com>",
	0x0100,
	Plugin::Type::Effect,
	new PixmapLoader("noemixerr-plugin-logo"),
	nullptr,
	nullptr,
} ;

}

// We have to keep a list of all the PeakController effects so that we can save
// an peakEffect-ID to the project.  This ID is referenced in the PeakController
// settings and is used to set the PeakControllerEffect pointer upon load

//QVector<PeakControllerEffect *> PeakControllerEffect::s_effects;

PeakControllerEffect::PeakControllerEffect(
			Model * _parent,
			const Descriptor::SubPluginFeatures::Key * _key ) :
	Effect( &peakcontrollereffect_plugin_descriptor, _parent, _key ),
	m_effectId(fastRand()),
	m_peakControls( this ),
	m_lastSample( 0 ),
	m_autoController( nullptr )
{
	m_autoController = new PeakController( Engine::getSong(), this );
	if( !Engine::getSong()->isLoadingProject() && !PresetPreviewPlayHandle::isPreviewing() )
	{
		Engine::getSong()->addController( m_autoController );
	}
	PeakController::s_effects.push_back(this);
}




PeakControllerEffect::~PeakControllerEffect()
{
	auto it = std::find(PeakController::s_effects.begin(), PeakController::s_effects.end(), this);
	if (it != PeakController::s_effects.end())
	{
		PeakController::s_effects.erase(it);
		Engine::getSong()->removeController(m_autoController);
	}
}


Effect::ProcessStatus PeakControllerEffect::processImpl(SampleFrame* buf, const f_cnt_t frames)
{
	PeakControllerEffectControls & c = m_peakControls;

	// RMS:
	double sum = 0;

	if( c.m_absModel.value() )
	{
		for (auto i = std::size_t{0}; i < frames; ++i)
		{
			// absolute value is achieved because the squares are > 0
			sum += buf[i][0] * buf[i][0] + buf[i][1] * buf[i][1];
		}
	}
	else
	{
		for (auto i = std::size_t{0}; i < frames; ++i)
		{
			// the value is absolute because of squaring,
			// so we need to correct it
			sum += buf[i][0] * buf[i][0] * sign(buf[i][0])
				+ buf[i][1] * buf[i][1] * sign(buf[i][1]);
		}
	}

	// TODO: flipping this might cause clipping
	// this will mute the output after the values were measured
	if( c.m_muteModel.value() )
	{
		for (auto i = std::size_t{0}; i < frames; ++i)
		{
			buf[i][0] = buf[i][1] = 0.0f;
		}
	}

	float curRMS = sqrt_neg(sum / frames);
	const float tres = c.m_tresholdModel.value();
	const float amount = c.m_amountModel.value() * c.m_amountMultModel.value();
	curRMS = qAbs( curRMS ) < tres ? 0.0f : curRMS;
	m_lastSample = qBound( 0.0f, c.m_baseModel.value() + amount * curRMS, 1.0f );

	return ProcessStatus::Continue;
}




extern "C"
{

// necessary for getting instance out of shared lib
PLUGIN_EXPORT Plugin * noemixerr_plugin_main( Model * _parent, void * _data )
{
	return new PeakControllerEffect( _parent,
		static_cast<const Plugin::Descriptor::SubPluginFeatures::Key *>( _data ) );
}

}


} // namespace noemixerr
