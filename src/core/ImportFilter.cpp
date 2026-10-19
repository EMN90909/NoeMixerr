// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <memory>
#include <QMessageBox>

#include "ImportFilter.h"
#include "Engine.h"
#include "TrackContainer.h"
#include "PluginFactory.h"
#include "ProjectJournal.h"


namespace noemixerr
{

using std::unique_ptr;

ImportFilter::ImportFilter( const QString & _file_name,
							const Descriptor * _descriptor ) :
	Plugin( _descriptor, nullptr ),
	m_file( _file_name )
{
}





void ImportFilter::import( const QString & _file_to_import,
							TrackContainer* tc )
{
	bool successful = false;

	QByteArray s = _file_to_import.toUtf8();
	s.detach();

	// do not record changes while importing files
	const bool j = Engine::projectJournal()->isJournalling();
	Engine::projectJournal()->setJournalling( false );

	for (const Plugin::Descriptor* desc : getPluginFactory()->descriptors(Plugin::Type::ImportFilter))
	{
		unique_ptr<Plugin> p(Plugin::instantiate( desc->name, nullptr, s.data() ));
		if( dynamic_cast<ImportFilter *>( p.get() ) != nullptr &&
			dynamic_cast<ImportFilter *>( p.get() )->tryImport( tc ) )
		{
			successful = true;
			break;
		}
	}

	Engine::projectJournal()->setJournalling( j );

	if( successful == false )
	{
		QMessageBox::information( nullptr,
			TrackContainer::tr( "Couldn't import file" ),
			TrackContainer::tr( "Couldn't find a filter for "
						"importing file %1.\n"
						"You should convert this file "
						"into a format supported by "
						"NoeMixerr using another software."
						).arg( _file_to_import ),
					QMessageBox::Ok,
					QMessageBox::NoButton );
	}
}




bool ImportFilter::openFile()
{
	if( m_file.open( QFile::ReadOnly ) == false )
	{
		QMessageBox::critical( nullptr,
			TrackContainer::tr( "Couldn't open file" ),
			TrackContainer::tr( "Couldn't open file %1 "
						"for reading.\nPlease make "
						"sure you have read-"
						"permission to the file and "
						"the directory containing the "
						"file and try again!" ).arg(
							m_file.fileName() ),
					QMessageBox::Ok,
					QMessageBox::NoButton );
		return false;
	}
	return true;
}



} // namespace noemixerr