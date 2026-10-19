// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_JOURNALLING_OBJECT_H
#define NoeMixerr_JOURNALLING_OBJECT_H

#include <QStack>

#include "NoeMixerrTypes.h"
#include "SerializingObject.h"

namespace noemixerr
{

class NoeMixerr_EXPORT JournallingObject : public SerializingObject
{
public:
	JournallingObject();
	~JournallingObject() override;

	inline jo_id_t id() const
	{
		return m_id;
	}

	void saveJournallingState( const bool newState )
	{
		m_journallingStateStack.push( m_journalling );
		m_journalling = newState;
	}

	void restoreJournallingState()
	{
		if( !isJournallingStateStackEmpty())
		{
			m_journalling = m_journallingStateStack.pop();
		}
	}

	void addJournalCheckPoint();

	QDomElement saveState( QDomDocument & _doc,
									QDomElement & _parent ) override;

	void restoreState( const QDomElement & _this ) override;

	inline bool isJournalling() const
	{
		return m_journalling;
	}

	inline void setJournalling( const bool _sr )
	{
		m_journalling = _sr;
	}

	inline bool testAndSetJournalling( const bool newState )
	{
		const bool oldJournalling = m_journalling;
		m_journalling = newState;
		return oldJournalling;
	}

	bool isJournallingStateStackEmpty() const
	{
		return m_journallingStateStack.isEmpty();
	}

protected:
	void changeID( jo_id_t _id );


private:
	jo_id_t m_id;

	bool m_journalling;

	QStack<bool> m_journallingStateStack;

} ;


} // namespace noemixerr

#endif // NoeMixerr_JOURNALLING_OBJECT_H
