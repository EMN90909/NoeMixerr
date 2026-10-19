// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2015 Maurizio Lo Bosco (rageboge on github)
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_APPLE_H
#define NoeMixerr_MIDI_APPLE_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_BUILD_APPLE

#include "MidiClient.h"
#include "MidiPort.h"
#include <CoreMIDI/CoreMIDI.h>


class QLineEdit;


namespace noemixerr
{


class MidiApple : public QObject, public MidiClient
{
	Q_OBJECT
public:
	MidiApple();
	virtual ~MidiApple();

	inline static QString probeDevice()
	{
		return QString(); // no midi device name
	}

	inline static QString name()
	{
		return QT_TRANSLATE_NOOP( "MidiSetupWidget", "Apple MIDI" );
	}
	inline static QString configSection()
	{
		return QString(); // no configuration settings
	}
	
	virtual void processOutEvent( const MidiEvent & _me,
								const TimePos & _time,
								const MidiPort * _port );
	
	virtual void applyPortMode( MidiPort * _port );
	virtual void removePort( MidiPort * _port );


	// list devices as ports
	virtual QStringList readablePorts() const
	{
		return m_inputDevices.keys();
	}

	virtual QStringList writablePorts() const
	{
		return m_outputDevices.keys();
	}

	// return name of port which specified MIDI event came from
	virtual QString sourcePortName( const MidiEvent & ) const;

	// (un)subscribe given MidiPort to/from destination-port
	virtual void subscribeReadablePort( MidiPort * _port,
									const QString & _dest,
									bool _subscribe = true );

	virtual void subscribeWritablePort( MidiPort * _port,
									const QString & _dest,
									bool _subscribe = true );

	virtual void connectRPChanged( QObject * _receiver,
									const char * _member )
	{
		connect( this, SIGNAL( readablePortsChanged() ),
				_receiver, _member );
	}


	virtual void connectWPChanged( QObject * _receiver,
									const char * _member )
	{
		connect( this, SIGNAL( writablePortsChanged() ),
				_receiver, _member );
	}


	virtual bool isRaw() const
	{
		return false;
	}


private:// slots:
	void updateDeviceList();


private:
	void openDevices();
	void closeDevices();
	void openMidiReference( MIDIEndpointRef reference, QString refName,bool isIn );
	MIDIClientRef getMidiClientRef();
	void midiInClose( MIDIEndpointRef reference );
	static void NotifyCallback( const MIDINotification *message, void *refCon );
	static void ReadCallback( const MIDIPacketList *pktlist, void *readProcRefCon, void *srcConnRefCon );
	void HandleReadCallback( const MIDIPacketList *pktlist, void *srcConnRefCon );
	void notifyMidiPortList( MidiPortList portList, MidiEvent midiEvent);
	char * getFullName( MIDIEndpointRef &endpoint_ref );
	void sendMidiOut( MIDIEndpointRef & endPointRef, const MidiEvent& event );
	MIDIPacketList createMidiPacketList( const MidiEvent& event );

	MIDIClientRef mClient = 0;
	QMap<QString, MIDIEndpointRef> m_inputDevices;
	QMap<QString, MIDIEndpointRef> m_outputDevices;
	QMap<MIDIEndpointRef, MIDIPortRef> m_sourcePortRef;

	// subscriptions
	using SubMap = QMap<QString, MidiPortList>;
	SubMap m_inputSubs;
	SubMap m_outputSubs;

signals:
	void readablePortsChanged();
	void writablePortsChanged();

} ;


} // namespace noemixerr

#endif // NoeMixerr_BUILD_APPLE

#endif // NoeMixerr_MIDI_APPLE_H
