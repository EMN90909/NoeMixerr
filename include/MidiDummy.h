// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_DUMMY_H
#define NoeMixerr_MIDI_DUMMY_H

#include "MidiClient.h"


namespace noemixerr
{


class MidiDummy : public MidiClientRaw
{
public:
	MidiDummy() = default;
	~MidiDummy() override = default;

	inline static QString name()
	{
		return( QT_TRANSLATE_NOOP( "MidiSetupWidget",
			"Dummy (no MIDI support)" ) );
	}

	inline static QString probeDevice()
	{
		return QString(); // no midi device name
	}

	inline static QString configSection()
	{
		return QString(); // no configuration settings
	}


protected:
	void sendByte( const unsigned char ) override
	{
	}

} ;


} // namespace noemixerr

#endif // NoeMixerr_MIDI_DUMMY_H
