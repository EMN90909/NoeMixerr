// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_WINMM_H
#define NoeMixerr_MIDI_WINMM_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_WINMM
#include <windows.h>
#include <mmsystem.h>

#include "MidiClient.h"
#include "MidiPort.h"


class QLineEdit;


namespace noemixerr
{


class MidiWinMM : public QObject, public MidiClient
{
	Q_OBJECT
public:
	MidiWinMM();
	virtual ~MidiWinMM();

	inline static QString probeDevice()
	{
		return QString(); // no midi device name
	}


	inline static QString name()
	{
		return QT_TRANSLATE_NOOP( "MidiSetupWidget", "WinMM MIDI" );
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
		return m_inputDevices.values();
	}

	virtual QStringList writablePorts() const
	{
		return m_outputDevices.values();
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

	static void WINAPI CALLBACK inputCallback( HMIDIIN _hm, UINT _msg,
						DWORD_PTR _inst,
						DWORD_PTR _param1,
							DWORD_PTR _param2 );
	void handleInputEvent( HMIDIIN _hm, DWORD _ev );

	QMap<HMIDIIN, QString> m_inputDevices;
	QMap<HMIDIOUT, QString> m_outputDevices;

	// subscriptions
	using SubMap = QMap<QString, MidiPortList>;
	SubMap m_inputSubs;
	SubMap m_outputSubs;


signals:
	void readablePortsChanged();
	void writablePortsChanged();

} ;


} // namespace noemixerr

#endif // NoeMixerr_HAVE_WINMM

#endif // NoeMixerr_MIDI_WINMM_H
