// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PROJECT_JOURNAL_H
#define NoeMixerr_PROJECT_JOURNAL_H

#include <QHash>
#include <QStack>

#include "NoeMixerrTypes.h"
#include "DataFile.h"


namespace noemixerr
{


class JournallingObject;


//! @warning many parts of this class may be rewritten soon
class ProjectJournal
{
public:
	static const int MAX_UNDO_STATES;

	ProjectJournal();
	virtual ~ProjectJournal() = default;

	void undo();
	void redo();

	bool canUndo() const;
	bool canRedo() const;

	void addJournalCheckPoint( JournallingObject *jo );

	bool isJournalling() const
	{
		return m_journalling;
	}

	void setJournalling( const bool _on )
	{
		m_journalling = _on;
	}

	// alloc new ID and register object _obj to it
	jo_id_t allocID( JournallingObject * _obj );

	// if there's already something known about ID _id, but it is currently
	// unused (e.g. after jouralling object was deleted), register object
	// _obj to this id
	void reallocID( const jo_id_t _id, JournallingObject * _obj );

	// make ID _id unused, but keep all global journalling information
	// (order of journalling entries etc.) referring to _id - needed for
	// restoring a journalling object later
	void freeID( const jo_id_t _id )
	{
		reallocID( _id, nullptr );
	}

	//! hack, not used when saving a file
	static jo_id_t idToSave( jo_id_t id );
	//! hack, not used when loading a savefile
	static jo_id_t idFromSave( jo_id_t id );

	void clearJournal();
	void stopAllJournalling();
	JournallingObject * journallingObject( const jo_id_t _id )
	{
		if( m_joIDs.contains( _id ) )
		{
			return m_joIDs[_id];
		}
		return nullptr;
	}


private:
	using JoIdMap = QHash<jo_id_t, JournallingObject*>;

	struct CheckPoint
	{
		CheckPoint( jo_id_t initID = 0, const DataFile& initData = DataFile( DataFile::Type::JournalData ) ) :
			joID( initID ),
			data( initData )
		{
		}
		jo_id_t joID;
		DataFile data;
	} ;
	using CheckPointStack = QStack<CheckPoint>;

	JoIdMap m_joIDs;

	CheckPointStack m_undoCheckPoints;
	CheckPointStack m_redoCheckPoints;

	bool m_journalling;

} ;


} // namespace noemixerr

#endif // NoeMixerr_PROJECT_JOURNAL_H
