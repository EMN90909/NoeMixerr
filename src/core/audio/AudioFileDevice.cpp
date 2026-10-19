// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QMessageBox>

#include "AudioFileDevice.h"
#include "ExportProjectDialog.h"
#include "GuiApplication.h"

namespace noemixerr
{

AudioFileDevice::AudioFileDevice( OutputSettings const & outputSettings,
					const ch_cnt_t _channels,
					const QString & _file,
					AudioEngine*  _audioEngine ) :
	AudioDevice( _channels, _audioEngine ),
	m_outputFile( _file ),
	m_outputSettings(outputSettings)
{
	using gui::ExportProjectDialog;

	setSampleRate( outputSettings.getSampleRate() );

	if( m_outputFile.open( QFile::WriteOnly | QFile::Truncate ) == false )
	{
		QString title, message;
		title = ExportProjectDialog::tr( "Could not open file" );
		message = ExportProjectDialog::tr( "Could not open file %1 "
						"for writing.\nPlease make "
						"sure you have write "
						"permission to the file and "
						"the directory containing the "
						"file and try again!"
								).arg( _file );

		if (gui::getGUI() != nullptr)
		{
			QMessageBox::critical( nullptr, title, message,
						QMessageBox::Ok,
						QMessageBox::NoButton );
		}
		else
		{
			fprintf( stderr, "%s\n", message.toUtf8().constData() );
			exit( EXIT_FAILURE );
		}
	}
}




AudioFileDevice::~AudioFileDevice()
{
	m_outputFile.close();
}




int AudioFileDevice::writeData( const void* data, int len )
{
	if( m_outputFile.isOpen() )
	{
		return m_outputFile.write( (const char *) data, len );
	}

	return -1;
}

} // namespace noemixerr
