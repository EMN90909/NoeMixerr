// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "InstrumentPlayHandle.h"
#include "Instrument.h"
#include "InstrumentTrack.h"
#include "Engine.h"
#include "AudioEngine.h"

namespace noemixerr
{


InstrumentPlayHandle::InstrumentPlayHandle(Instrument * instrument, InstrumentTrack* instrumentTrack) :
	PlayHandle(Type::InstrumentPlayHandle),
	m_instrument(instrument)
{
	setAudioBusHandle(instrumentTrack->audioBusHandle());
}

void InstrumentPlayHandle::play(SampleFrame* working_buffer)
{
	InstrumentTrack * instrumentTrack = m_instrument->instrumentTrack();

	// ensure that all our nph's have been processed first
	auto nphv = NotePlayHandle::nphsOfInstrumentTrack(instrumentTrack, true);

	bool nphsLeft;
	do
	{
		nphsLeft = false;
		for (const auto& handle : nphv)
		{
			if (handle->state() != ThreadableJob::ProcessingState::Done && !handle->isFinished())
			{
				nphsLeft = true;
				const_cast<NotePlayHandle*>(handle)->process();
			}
		}
	}
	while (nphsLeft);

	m_instrument->play(working_buffer);

	// Process the audio buffer that the instrument has just worked on...
	const f_cnt_t frames = Engine::audioEngine()->framesPerPeriod();
	instrumentTrack->processAudioBuffer(working_buffer, frames, nullptr);
}

bool InstrumentPlayHandle::isFromTrack(const Track* track) const
{
	return m_instrument->isFromTrack(track);
}


} // namespace noemixerr
