// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_SERIALIZING_OBJECT_H
#define NoeMixerr_SERIALIZING_OBJECT_H

#include <QString>

#include "noemixerr_export.h"


class QDomDocument;
class QDomElement;

namespace noemixerr
{

class SerializingObjectHook;


class NoeMixerr_EXPORT SerializingObject
{
public:
	SerializingObject();
	virtual ~SerializingObject();

	virtual QDomElement saveState( QDomDocument & _doc, QDomElement & _parent );

	virtual void restoreState( const QDomElement & _this );


	// to be implemented by actual object
	virtual QString nodeName() const = 0;

	void setHook( SerializingObjectHook * _hook );

	SerializingObjectHook* hook()
	{
		return m_hook;
	}


protected:
	// to be implemented by sub-objects
	virtual void saveSettings( QDomDocument& doc, QDomElement& element ) = 0;
	virtual void loadSettings( const QDomElement& element ) = 0;


private:
	SerializingObjectHook * m_hook;

} ;


class SerializingObjectHook
{
public:
	SerializingObjectHook() :
		m_hookedIn( nullptr )
	{
	}
	virtual ~SerializingObjectHook()
	{
		if( m_hookedIn != nullptr )
		{
			m_hookedIn->setHook( nullptr );
		}
	}

	virtual void saveSettings( QDomDocument & _doc, QDomElement & _this ) = 0;
	virtual void loadSettings( const QDomElement & _this ) = 0;

private:
	SerializingObject * m_hookedIn;

	friend class SerializingObject;

} ;


} // namespace noemixerr

#endif // NoeMixerr_SERIALIZING_OBJECT_H
