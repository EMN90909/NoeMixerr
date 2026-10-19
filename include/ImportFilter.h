// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_IMPORT_FILTER_H
#define NoeMixerr_IMPORT_FILTER_H

#include <QFile>

#include "Plugin.h"

namespace noemixerr
{


class TrackContainer;


class NoeMixerr_EXPORT ImportFilter : public Plugin
{
public:
	ImportFilter( const QString & _file_name,
					const Descriptor * _descriptor );
	~ImportFilter() override = default;


	// tries to import given file to given track-container by having all
	// available import-filters to try to import the file
	static void import( const QString & _file_to_import,
						TrackContainer* tc );


protected:
	virtual bool tryImport( TrackContainer* tc ) = 0;

	const QFile & file() const
	{
		return m_file;
	}

	bool openFile();

	inline void closeFile()
	{
		m_file.close();
	}

	inline int readByte()
	{
		unsigned char c;
		if( m_file.getChar( (char*) &c ) )
		{
			return static_cast<int>( c );
		}
		return -1;
	}

	inline int readBlock( char * _data, int _len )
	{
		return m_file.read( _data, _len );
	}

	inline QByteArray readAllData()
	{
		m_file.seek(0);
		return m_file.readAll();
	}

	inline void ungetChar( char _ch )
	{
		m_file.ungetChar( _ch );
	}

	void saveSettings( QDomDocument &, QDomElement & ) override
	{
	}

	void loadSettings( const QDomElement & ) override
	{
	}

	QString nodeName() const override
	{
		return "import_filter";
	}


private:
	QFile m_file;

} ;


} // namespace noemixerr

#endif // NoeMixerr_IMPORT_FILTER_H
