// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2013 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_ALSA_SEQ_H
#define NoeMixerr_MIDI_ALSA_SEQ_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_ALSA
#include <alsa/asoundlib.h>

#include <QMap>
#include <QMutex>
#include <QThread>
#include <QTimer>


#include "MidiClient.h"




namespace noemixerr
{


class MidiAlsaSeq : public QThread, public MidiClient
{
	Q_OBJECT
public:
	MidiAlsaSeq();
	~MidiAlsaSeq() override;

	static QString probeDevice();


	inline static QString name()
	{
		return QT_TRANSLATE_NOOP( "MidiSetupWidget",
			"ALSA-Sequencer (Advanced Linux Sound "
							"Architecture)" );
	}

	inline static QString configSection()
	{
		return "Midialsaseq";
	}



	void processOutEvent( const MidiEvent & _me,
						const TimePos & _time,
						const MidiPort * _port ) override;

	void applyPortMode( MidiPort * _port ) override;
	void applyPortName( MidiPort * _port ) override;

	void removePort( MidiPort * _port ) override;


	// list seq-ports from ALSA
	QStringList readablePorts() const override
	{
		return m_readablePorts;
	}

	QStringList writablePorts() const override
	{
		return m_writablePorts;
	}

	// return name of port which specified MIDI event came from
	QString sourcePortName( const MidiEvent & ) const override;

	// (un)subscribe given MidiPort to/from destination-port
	void subscribeReadablePort( MidiPort * _port,
						const QString & _dest,
						bool _subscribe = true ) override;
	void subscribeWritablePort( MidiPort * _port,
						const QString & _dest,
						bool _subscribe = true ) override;
	void connectRPChanged( QObject * _receiver,
							const char * _member ) override
	{
		connect( this, SIGNAL( readablePortsChanged() ),
							_receiver, _member );
	}

	void connectWPChanged( QObject * _receiver,
							const char * _member ) override
	{
		connect( this, SIGNAL( writablePortsChanged() ),
							_receiver, _member );
	}


private slots:
	void changeQueueTempo( noemixerr::bpm_t _bpm );
	void updatePortList();


private:
	void run() override;

#ifdef NoeMixerr_HAVE_ALSA
	QMutex m_seqMutex;
	snd_seq_t * m_seqHandle;
	struct Ports
	{
		Ports() { p[0] = -1; p[1] = -1; }
		int & operator[]( const int _i ) { return p[_i]; }
		private: int p[2];
	} ;
	QMap<MidiPort *, Ports> m_portIDs;
#endif

	int m_queueID;

	volatile bool m_quit;

	QTimer m_portListUpdateTimer;
	QStringList m_readablePorts;
	QStringList m_writablePorts;

	int m_pipe[2];


signals:
	void readablePortsChanged();
	void writablePortsChanged();

} ;


} // namespace noemixerr

#endif // NoeMixerr_HAVE_ALSA

#endif // NoeMixerr_MIDI_ALSA_SEQ_H
