// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PIANO_H
#define NoeMixerr_PIANO_H

#include <array>

#include "Model.h"
#include "Note.h"

namespace noemixerr
{


class InstrumentTrack;
class MidiEventProcessor;

class Piano final : public Model
{
public:
	enum class KeyType
	{
		White,
		Black
	} ;

	//! @brief Create a new keyboard display
	//!
	//! @param track The InstrumentTrack window to attach to
	Piano(InstrumentTrack* track);

	//! @brief Turn a key on or off
	//!
	//! @param key the key number to change
	//! @param state the state to set the key to
	void setKeyState(int key, bool state);

	bool isKeyPressed(int key) const
	{
		return m_pressedKeys[key];
	}

	//! @brief Handle a note being pressed on our keyboard display
	//!
	//! @param key the key being pressed
	//! @param midiVelocity An optional MIDI velocity override
	void handleKeyPress(int key, int midiVelocity = -1);

	//! @brief Handle a note being released on our keyboard display
	//!
	//! @param key the key being releassed
	void handleKeyRelease(int key);

	InstrumentTrack* instrumentTrack() const
	{
		return m_instrumentTrack;
	}

	MidiEventProcessor* midiEventProcessor() const
	{
		return m_midiEvProc;
	}

	static bool isWhiteKey(int key);
	static bool isBlackKey(int key);

	static const unsigned int WhiteKeysPerOctave = 7;
	static const unsigned int BlackKeysPerOctave = 5;
	static const unsigned int NumWhiteKeys = 75;
	static const unsigned int NumBlackKeys = 53;

private:
	static bool isValidKey(int key)
	{
		return key >= 0 && key < NumKeys;
	}

	InstrumentTrack* m_instrumentTrack;
	MidiEventProcessor* m_midiEvProc;
	std::array<bool, NumKeys> m_pressedKeys = {};

} ;


} // namespace noemixerr

#endif // NoeMixerr_PIANO_H
