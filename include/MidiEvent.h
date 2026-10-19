// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_EVENT_H
#define NoeMixerr_MIDI_EVENT_H

#include <cstdlib>
#include "Midi.h"
#include "panning.h"
#include "volume.h"

namespace noemixerr
{

class MidiEvent
{
public:
	enum class Source { Internal, External };

	MidiEvent(MidiEventTypes type = MidiActiveSensing,
				int8_t channel = 0,
				int16_t param1 = 0,
				int16_t param2 = 0,
				const void* sourcePort = nullptr,
				Source source = Source::External) :
		m_type( type ),
		m_metaEvent( MidiMetaInvalid ),
		m_channel( channel ),
		m_sysExData( nullptr ),
		m_sourcePort(sourcePort),
		m_source(source)
	{
		m_data.m_param[0] = param1;
		m_data.m_param[1] = param2;
	}

	MidiEvent(MidiEventTypes type, const char* sysExData, std::size_t dataLen, Source source = Source::External) :
		m_type( type ),
		m_metaEvent( MidiMetaInvalid ),
		m_channel( 0 ),
		m_sysExData( sysExData ),
		m_sourcePort(nullptr),
		m_source(source)
	{
		m_data.m_sysExDataLen = dataLen;
	}

	MidiEvent( const MidiEvent& other ) = default;

	MidiEventTypes type() const
	{
		return m_type;
	}

	void setType( MidiEventTypes type )
	{
		m_type = type;
	}

	void setMetaEvent( MidiMetaEventType metaEvent )
	{
		m_metaEvent = metaEvent;
	}

	MidiMetaEventType metaEvent() const
	{
		return m_metaEvent;
	}

	int8_t channel() const
	{
		return m_channel;
	}

	void setChannel( int8_t channel )
	{
		m_channel = channel;
	}

	int16_t param( int i ) const
	{
		return m_data.m_param[i];
	}

	void setParam( int i, uint16_t value )
	{
		m_data.m_param[i] = value;
	}

	int16_t key() const
	{
		return param( 0 );
	}

	void setKey( int16_t key )
	{
		m_data.m_param[0] = key;
	}

	uint8_t velocity() const
	{
		return m_data.m_param[1] & 0x7F;
	}

	void setVelocity( int16_t velocity )
	{
		m_data.m_param[1] = velocity;
	}

	panning_t panning() const
	{
		return (panning_t) ( PanningLeft +
			( (float)( midiPanning() - MidiMinPanning ) ) / 
			( (float)( MidiMaxPanning - MidiMinPanning ) ) *
			( (float)( PanningRight - PanningLeft ) ) );
	}
	int16_t midiPanning() const
	{
		return m_data.m_param[1];
	}

	volume_t volume( int midiBaseVelocity ) const
	{
		return (volume_t)( velocity() * DefaultVolume / midiBaseVelocity );
	}

	const void* sourcePort() const
	{
		return m_sourcePort;
	}

	uint8_t controllerNumber() const
	{
		return param( 0 ) & 0x7F;
	}

	void setControllerNumber( uint8_t num )
	{
		setParam( 0, num );
	}

	uint8_t controllerValue() const
	{
		return param( 1 );
	}

	void setControllerValue( uint8_t value )
	{
		setParam( 1, value );
	}

	uint8_t program() const
	{
		return param( 0 );
	}

	uint8_t channelPressure() const
	{
		return param( 0 );
	}

	int16_t pitchBend() const
	{
		return param( 0 );
	}

	void setPitchBend( uint16_t pitchBend )
	{
		setParam( 0, pitchBend );
	}

	auto sysExData() const -> const char* { return m_sysExData; }

	Source source() const
	{
		return m_source;
	}

	void setSource(Source value)
	{
		m_source = value;
	}


private:
	MidiEventTypes m_type;		// MIDI event type
	MidiMetaEventType m_metaEvent;	// Meta event (mostly unused)
	int8_t m_channel;		// MIDI channel
	union
	{
		int16_t m_param[2];	// first/second parameter (key/velocity)
		uint8_t m_bytes[4];	// raw bytes
		int32_t m_sysExDataLen;	// len of m_sysExData
	} m_data;

	const char* m_sysExData;
	const void* m_sourcePort;

	// Stores the source of the MidiEvent: Internal or External (hardware controllers).
	Source m_source;
} ;

} // namespace noemixerr

#endif // NoeMixerr_MIDI_EVENT_H
