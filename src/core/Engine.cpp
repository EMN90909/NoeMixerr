// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "Engine.h"
#include "AudioEngine.h"
#include "ConfigManager.h"
#include "Mixer.h"
#include "Ladspa2NoeMixerr.h"
#include "Lv2Manager.h"
#include "PatternStore.h"
#include "Plugin.h"
#include "PresetPreviewPlayHandle.h"
#include "ProjectJournal.h"
#include "Song.h"
#include "BandLimitedWave.h"
#include "Oscillator.h"

namespace noemixerr
{

float Engine::s_framesPerTick;
AudioEngine* Engine::s_audioEngine = nullptr;
Mixer * Engine::s_mixer = nullptr;
PatternStore * Engine::s_patternStore = nullptr;
Song * Engine::s_song = nullptr;
ProjectJournal * Engine::s_projectJournal = nullptr;
#ifdef NoeMixerr_HAVE_LV2
Lv2Manager * Engine::s_lv2Manager = nullptr;
#endif
Ladspa2NoeMixerr * Engine::s_ladspaManager = nullptr;
void* Engine::s_dndPluginKey = nullptr;




void Engine::init( bool renderOnly )
{
	Engine *engine = inst();

	emit engine->initProgress(tr("Generating wavetables"));
	// generate (load from file) bandlimited wavetables
	BandLimitedWave::generateWaves();
	//initialize oscillators
	Oscillator::waveTableInit();

	emit engine->initProgress(tr("Initializing data structures"));
	s_projectJournal = new ProjectJournal;
	s_audioEngine = new AudioEngine( renderOnly );
	s_song = new Song;
	s_mixer = new Mixer;
	s_patternStore = new PatternStore;

#ifdef NoeMixerr_HAVE_LV2
	s_lv2Manager = new Lv2Manager;
	s_lv2Manager->initPlugins();
#endif
	s_ladspaManager = new Ladspa2NoeMixerr;

	s_projectJournal->setJournalling( true );

	emit engine->initProgress(tr("Opening audio and midi devices"));
	s_audioEngine->initDevices();

	PresetPreviewPlayHandle::init();

	emit engine->initProgress(tr("Launching audio engine threads"));
	s_audioEngine->startProcessing();
}




void Engine::destroy()
{
	s_projectJournal->stopAllJournalling();
	s_audioEngine->stopProcessing();

	PresetPreviewPlayHandle::cleanup();

	s_song->clearProject();

	deleteHelper( &s_patternStore );

	deleteHelper( &s_mixer );
	deleteHelper( &s_audioEngine );

#ifdef NoeMixerr_HAVE_LV2
	deleteHelper( &s_lv2Manager );
#endif
	deleteHelper( &s_ladspaManager );

	//delete ConfigManager::inst();
	deleteHelper( &s_projectJournal );

	deleteHelper( &s_song );

	delete ConfigManager::inst();

	// The oscillator FFT plans remain throughout the application lifecycle
	// due to being expensive to create, and being used whenever a userwave form is changed
	Oscillator::destroyFFTPlans();
}




float Engine::framesPerTick(sample_rate_t sampleRate)
{
	return sampleRate * 60.0f * 4 /
			DefaultTicksPerBar / s_song->getTempo();
}




void Engine::updateFramesPerTick()
{
	s_framesPerTick = s_audioEngine->outputSampleRate() * 60.0f * 4 / DefaultTicksPerBar / s_song->getTempo();
}




void Engine::setDndPluginKey(void *newKey)
{
	Q_ASSERT(static_cast<Plugin::Descriptor::SubPluginFeatures::Key*>(newKey));
	s_dndPluginKey = newKey;
}




void *Engine::pickDndPluginKey()
{
	return s_dndPluginKey;
}




Engine * Engine::s_instanceOfMe = nullptr;

} // namespace noemixerr
