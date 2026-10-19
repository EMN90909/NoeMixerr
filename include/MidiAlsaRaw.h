// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_ALSA_RAW_H
#define NoeMixerr_MIDI_ALSA_RAW_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_ALSA

#include <alsa/asoundlib.h>

#include <QThread>

#include "MidiClient.h"


struct pollfd;


namespace noemixerr
{

class MidiAlsaRaw : public QThread, public MidiClientRaw
{
	Q_OBJECT
public:
	MidiAlsaRaw();
	~MidiAlsaRaw() override;

	static QString probeDevice();


	inline static QString name()
	{
		return QT_TRANSLATE_NOOP( "MidiSetupWidget",
			"ALSA Raw-MIDI (Advanced Linux Sound Architecture)" );
	}

	inline static QString configSection()
	{
		return "MidiAlsaRaw";
	}


protected:
	void sendByte( const unsigned char c ) override;
	void run() override;


private:
	snd_rawmidi_t * m_input, * * m_inputp;
	snd_rawmidi_t * m_output, * * m_outputp;
	int m_npfds;
	pollfd * m_pfds;

	volatile bool m_quit;

} ;


} // namespace noemixerr

#endif // NoeMixerr_HAVE_ALSA

#endif // NoeMixerr_MIDI_ALSA_RAW_H
