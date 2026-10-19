// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QDir>
#include <QLabel>

#include "VstSubPluginFeatures.h"
#include "ConfigManager.h"
#include "Effect.h"

namespace noemixerr
{


VstSubPluginFeatures::VstSubPluginFeatures( Plugin::Type _type ) :
	SubPluginFeatures( _type )
{
}




void VstSubPluginFeatures::fillDescriptionWidget( QWidget * _parent,
													const Key * _key  ) const
{
	new QLabel( QWidget::tr( "Name: " ) + _key->name, _parent );
	new QLabel( QWidget::tr( "File: " ) + _key->attributes["file"], _parent );
}




void VstSubPluginFeatures::listSubPluginKeys( const Plugin::Descriptor * _desc,
														KeyList & _kl ) const
{
	auto dlls = new QStringList();
	const QString path = QString("");
	addPluginsFromDir(dlls, path );
	// TODO: eval m_type
	for( QStringList::ConstIterator it = dlls->begin();
							it != dlls->end(); ++it )
	{
		EffectKey::AttributeMap am;
		am["file"] = *it;
		_kl.push_back( Key( _desc, QFileInfo( *it ).baseName(), am ) );
	}
	delete dlls;
}

void VstSubPluginFeatures::addPluginsFromDir( QStringList* filenames, QString path ) const
{
	QStringList dirs = QDir ( ConfigManager::inst()->vstDir() + path ).
				entryList( QStringList() << "*" ,
						   QDir::Dirs, QDir::Name );
	for( int i = 0; i < dirs.size(); i++ )
	{
		if( dirs.at( i )[0] != '.' )
		{
			addPluginsFromDir( filenames, path+QDir::separator() + dirs.at( i ) );
		}
	}
	QStringList dlls = QDir( ConfigManager::inst()->vstDir() + path ).
				entryList( QStringList() << "*.dll"
#ifdef NoeMixerr_BUILD_LINUX
										 << "*.so"
#endif
						,
						QDir::Files, QDir::Name );
	for( int i = 0; i < dlls.size(); i++ )
	{
		QString fName = path + QDir::separator() + dlls.at( i );
		fName.remove( 0, 1 );
		filenames->append( fName );
	}
}


} // namespace noemixerr
