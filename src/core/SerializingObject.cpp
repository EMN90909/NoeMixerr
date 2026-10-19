// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QDomElement>

#include "SerializingObject.h"

namespace noemixerr
{

SerializingObject::SerializingObject() :
	m_hook( nullptr )
{
}




SerializingObject::~SerializingObject()
{
	if( m_hook )
	{
		m_hook->m_hookedIn = nullptr;
	}
}




QDomElement SerializingObject::saveState( QDomDocument& doc, QDomElement& parent )
{
	QDomElement element = doc.createElement( nodeName() );
	parent.appendChild( element );

	saveSettings( doc, element );

	if( hook() )
	{
		hook()->saveSettings( doc, element );
	}

	return element;
}




void SerializingObject::restoreState( const QDomElement& element )
{
	loadSettings( element );

	if( hook() )
	{
		hook()->loadSettings( element );
	}
}




void SerializingObject::setHook( SerializingObjectHook* hook )
{
	if( m_hook )
	{
		m_hook->m_hookedIn = nullptr;
	}

	m_hook = hook;

	if( m_hook )
	{
		m_hook->m_hookedIn = this;
	}
}




void SerializingObject::saveSettings( QDomDocument& doc, QDomElement& element )
{
	Q_UNUSED(doc)
	Q_UNUSED(element)
}




void SerializingObject::loadSettings( const QDomElement& element )
{
	Q_UNUSED(element)
}

} // namespace noemixerr
