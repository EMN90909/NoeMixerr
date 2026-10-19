// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2015 Shane Ambler <develop/at/shaneware.biz>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_JACK_H
#define NoeMixerr_MIDI_JACK_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_JACK
#ifndef NoeMixerr_HAVE_WEAKJACK
#include <jack/jack.h>
#include <jack/midiport.h>
#else
#include <weak_libjack.h>
#endif

#include <QThread>

#include "MidiClient.h"


namespace noemixerr
{

constexpr size_t JACK_MIDI_BUFFER_MAX = 64; /* events */

class AudioJack;

class MidiJack : public QThread, public MidiClientRaw
{
        Q_OBJECT
public:
	MidiJack();
	~MidiJack() override;

	jack_client_t* jackClient();

	static QString probeDevice();

	inline static QString name()
	{
		return( QT_TRANSLATE_NOOP( "MidiSetupWidget",
			"Jack-MIDI" ) );
	}

	void JackMidiWrite(jack_nframes_t nframes);
	void JackMidiRead(jack_nframes_t nframes);


	inline static QString configSection()
	{
		return "MidiJack";
	}


protected:
	void sendByte( const unsigned char c ) override;
	void run() override;


private:
	AudioJack *m_jackAudio;
	jack_client_t *m_jackClient;
	jack_port_t *m_input_port;
	jack_port_t *m_output_port;
	uint8_t m_jack_buffer[JACK_MIDI_BUFFER_MAX * 4];

	void JackMidiOutEvent(uint8_t *buf, uint8_t len);
	void lock();
	void unlock();

	void getPortInfo( const QString& sPortName, int& nClient, int& nPort );

	volatile bool m_quit;

};


} // namespace noemixerr

#endif // NoeMixerr_HAVE_JACK

#endif // NoeMixerr_MIDI_JACK_H
