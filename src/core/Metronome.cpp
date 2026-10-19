// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024 saker
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Metronome.h"

#include "Engine.h"
#include "SamplePlayHandle.h"

namespace noemixerr {
void Metronome::processTick(int currentTick, int ticksPerBar, int beatsPerBar, size_t bufferOffset)
{
	const auto ticksPerBeat = ticksPerBar / beatsPerBar;
	if (currentTick % ticksPerBeat != 0 || !m_active) { return; }

	const auto handle = currentTick % ticksPerBar == 0 ? new SamplePlayHandle("misc/metronome02.ogg")
													   : new SamplePlayHandle("misc/metronome01.ogg");
	handle->setOffset(bufferOffset);
	Engine::audioEngine()->addPlayHandle(handle);
}
} // namespace noemixerr
