// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020-2020 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "MidiEventToByteSeq.h"

#include <QtGlobal>

#include "MidiEvent.h"


namespace noemixerr
{


std::size_t writeToByteSeq(
	const MidiEvent& ev, uint8_t *data, std::size_t bufsize)
{
	Q_ASSERT(bufsize >= 3);

	std::size_t size = 0;
	data[0] = ev.type() | (ev.channel() & 0x0F);

	switch (ev.type())
	{
		case MidiNoteOn:
			if (ev.velocity() > 0)
			{
				if (ev.key() < 0 || ev.key() > MidiMaxKey)
					break;

				data[1] = ev.key();
				data[2] = ev.velocity();
				size    = 3;
				break;
			}
			else
			{
				// Lv2 MIDI specs:
				// "Note On messages with velocity 0 are not allowed.
				// These messages are equivalent to Note Off in standard
				// MIDI streams, but here only proper Note Off messages
				// are allowed."
				data[0] = MidiNoteOff | (ev.channel() & 0x0F);
				// nobreak
			}

		case MidiNoteOff:
			if (ev.key() < 0 || ev.key() > MidiMaxKey)
				break;
			data[1] = ev.key();
			data[2] = ev.velocity(); // release time
			size    = 3;
			break;

		case MidiKeyPressure:
			data[1] = ev.key();
			data[2] = ev.velocity();
			size    = 3;
			break;

		case MidiControlChange:
			data[1] = ev.controllerNumber();
			data[2] = ev.controllerValue();
			size    = 3;
			break;

		case MidiProgramChange:
			data[1] = ev.program();
			size    = 2;
			break;

		case MidiChannelPressure:
			data[1] = ev.channelPressure();
			size    = 2;
			break;

		case MidiPitchBend:
			data[1] = ev.pitchBend() & 0x7f;
			data[2] = ev.pitchBend() >> 7;
			size    = 3;
			break;

		default:
			// unhandled
			break;
	}

	return size;
}


} // namespace noemixerr
