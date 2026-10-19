// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2010-2016 jackmsr@openbsd.net
// Copyright (c) 2016-2017 David Carlier <devnexen@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "MidiSndio.h"

#ifdef NoeMixerr_HAVE_SNDIO

#include <cstdlib>
#include <sndio.h>
#include <poll.h>

#include "ConfigManager.h"


namespace noemixerr
{


MidiSndio::MidiSndio() :
	MidiClientRaw(),
	m_quit( false )
{
	QString dev = probeDevice();

	if (dev == "")
	{
		m_hdl = mio_open( nullptr, MIO_IN | MIO_OUT, 0 );
	}
	else
	{
		m_hdl = mio_open( dev.toLatin1().constData(), MIO_IN | MIO_OUT, 0 );
	}

	if( m_hdl == nullptr )
	{
		printf( "sndio: failed opening sndio midi device\n" );
		return;
	}

	start( QThread::LowPriority );
}


MidiSndio::~MidiSndio()
{
	if( isRunning() )
	{
		m_quit = true;
		wait( 1000 );
		terminate();
	}
}


QString MidiSndio::probeDevice()
{
	QString dev = ConfigManager::inst()->value( "MidiSndio", "device" );

	return dev ;
}


void MidiSndio::sendByte( const unsigned char c )
{
	mio_write( m_hdl, &c, 1 );
}


void MidiSndio::run()
{
	struct pollfd pfd;
	char buf[0x100];
	while( m_quit == false && m_hdl )
	{
		nfds_t nfds = mio_pollfd(m_hdl, &pfd, POLLIN);
		int ret = poll(&pfd, nfds, 100);
		if ( ret < 0 )
			break;
		if ( !ret || !( mio_revents( m_hdl, &pfd ) & POLLIN ) )
			continue;
		size_t n = mio_read(m_hdl, buf, sizeof(buf));
		if ( !n )
		{
			break;
		}
		for (char* p = buf; n > 0; n--, p++)
		{
			parseData( *p );
		}
	}
}


} // namespace noemixerr

#endif	// NoeMixerr_HAVE_SNDIO
