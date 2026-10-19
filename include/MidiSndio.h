// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2010-2016 jackmsr@openbsd.net
// Copyright (c) 2016-2017 David Carlier <devnexen@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_SNDIO_H
#define NoeMixerr_MIDI_SNDIO_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_SNDIO

#include <QThread>

#include "MidiClient.h"


struct mio_hdl;

namespace noemixerr
{


class MidiSndio : public QThread, public MidiClientRaw
{
	Q_OBJECT
public:
	MidiSndio();
	~MidiSndio() override;

	static QString probeDevice();

	inline static QString name()
	{
		return QT_TRANSLATE_NOOP("MidiSetupWidget", "sndio MIDI");
	}

	inline static QString configSection()
	{
		return "MidiSndio";
	}


protected:
	void sendByte(const unsigned char c) override;
	void run() override;

private:
	mio_hdl *m_hdl;
	volatile bool m_quit;
} ;


} // namespace noemixerr

#endif // NoeMixerr_HAVE_SNDIO

#endif // NoeMixerr_MIDI_SNDIO_H
