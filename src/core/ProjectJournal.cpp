// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <cstdlib>
#include <QDomElement>

#include "ProjectJournal.h"
#include "Engine.h"
#include "JournallingObject.h"
#include "noemixerr_math.h"
#include "Song.h"
#include "AutomationClip.h"

namespace noemixerr
{

//! Avoid clashes between loaded IDs (have the bit cleared)
//! and newly created IDs (have the bit set)
static const int EO_ID_MSB = 1 << 23;

const int ProjectJournal::MAX_UNDO_STATES = 100; // TODO: make this configurable in settings

ProjectJournal::ProjectJournal() :
	m_joIDs(),
	m_undoCheckPoints(),
	m_redoCheckPoints(),
	m_journalling( false )
{
}




void ProjectJournal::undo()
{
	while( !m_undoCheckPoints.isEmpty() )
	{
		CheckPoint c = m_undoCheckPoints.pop();
		JournallingObject *jo = m_joIDs[c.joID];

		if( jo )
		{
			DataFile curState( DataFile::Type::JournalData );
			jo->saveState( curState, curState.content() );
			m_redoCheckPoints.push( CheckPoint( c.joID, curState ) );

			bool prev = isJournalling();
			setJournalling( false );
			jo->restoreState( c.data.content().firstChildElement() );
			setJournalling( prev );
			Engine::getSong()->setModified();

			// loading AutomationClip connections correctly
			if (!c.data.content().elementsByTagName("automationclip").isEmpty())
			{
				AutomationClip::resolveAllIDs();
			}
			break;
		}
	}
}



void ProjectJournal::redo()
{
	while( !m_redoCheckPoints.isEmpty() )
	{
		CheckPoint c = m_redoCheckPoints.pop();
		JournallingObject *jo = m_joIDs[c.joID];

		if( jo )
		{
			DataFile curState( DataFile::Type::JournalData );
			jo->saveState( curState, curState.content() );
			m_undoCheckPoints.push( CheckPoint( c.joID, curState ) );

			bool prev = isJournalling();
			setJournalling( false );
			jo->restoreState( c.data.content().firstChildElement() );
			setJournalling( prev );
			Engine::getSong()->setModified();
			break;
		}
	}
}

bool ProjectJournal::canUndo() const
{
	return !m_undoCheckPoints.isEmpty();
}

bool ProjectJournal::canRedo() const
{
	return !m_redoCheckPoints.isEmpty();
}



void ProjectJournal::addJournalCheckPoint( JournallingObject *jo )
{
	if( isJournalling() )
	{
		m_redoCheckPoints.clear();

		DataFile dataFile( DataFile::Type::JournalData );
		jo->saveState( dataFile, dataFile.content() );

		m_undoCheckPoints.push( CheckPoint( jo->id(), dataFile ) );
		if( m_undoCheckPoints.size() > MAX_UNDO_STATES )
		{
			m_undoCheckPoints.remove( 0, m_undoCheckPoints.size() - MAX_UNDO_STATES );
		}
	}
}


jo_id_t ProjectJournal::allocID(JournallingObject* obj)
{
	jo_id_t id;
	for (jo_id_t tid = fastRand(); m_joIDs.contains(id = tid % EO_ID_MSB | EO_ID_MSB); tid++) {}
	m_joIDs[id] = obj;
	return id;
}


void ProjectJournal::reallocID( const jo_id_t _id, JournallingObject * _obj )
{
	//printf("realloc %d %d\n", _id, _obj );
//	if( m_joIDs.contains( _id ) )
	{
		m_joIDs[_id] = _obj;
	}
}




jo_id_t ProjectJournal::idToSave( jo_id_t id )
{
	return id & ~EO_ID_MSB;
}

jo_id_t ProjectJournal::idFromSave( jo_id_t id )
{
	return id | EO_ID_MSB;
}




void ProjectJournal::clearJournal()
{
	m_undoCheckPoints.clear();
	m_redoCheckPoints.clear();

	for( JoIdMap::Iterator it = m_joIDs.begin(); it != m_joIDs.end(); )
	{
		if( it.value() == nullptr )
		{
			it = m_joIDs.erase( it );
		}
		else
		{
			++it;
		}
	}
}

void ProjectJournal::stopAllJournalling()
{
	for( JoIdMap::Iterator it = m_joIDs.begin(); it != m_joIDs.end(); ++it)
	{
		if( it.value() != nullptr )
		{
			it.value()->setJournalling(false);
		}
	}
	setJournalling(false);
}



} // namespace noemixerr
