// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_EVENT_PROCESSOR_H
#define NoeMixerr_MIDI_EVENT_PROCESSOR_H

#include "MidiEvent.h"
#include "TimePos.h"

namespace noemixerr
{

// all classes being able to process MIDI-events should inherit from this
class MidiEventProcessor
{
public:
	MidiEventProcessor() = default;

	virtual ~MidiEventProcessor() = default;

	// to be implemented by inheriting classes
	virtual void processInEvent( const MidiEvent& event, const TimePos& time = TimePos(), f_cnt_t offset = 0 ) = 0;
	virtual void processOutEvent( const MidiEvent& event, const TimePos& time = TimePos(), f_cnt_t offset = 0 ) = 0;

} ;

} // namespace noemixerr

#endif // NoeMixerr_MIDI_EVENT_PROCESSOR_H
