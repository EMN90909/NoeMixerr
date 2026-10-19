// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_TRACK_CONTAINER_H
#define NoeMixerr_TRACK_CONTAINER_H

#include <QReadWriteLock>

#include "Track.h"
#include "JournallingObject.h"

namespace noemixerr
{

class AutomationClip;
class InstrumentTrack;

namespace gui
{

class TrackContainerView;

}


class NoeMixerr_EXPORT TrackContainer : public Model, public JournallingObject
{
	Q_OBJECT
public:
	using TrackList = std::vector<Track*>;
	enum class Type
	{
		Pattern,
		Song
	} ;

	TrackContainer();
	~TrackContainer() override;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;

	void loadSettings( const QDomElement & _this ) override;

	int countTracks( Track::Type _tt = Track::Type::Count ) const;


	void addTrack( Track * _track );
	void removeTrack( Track * _track );
	void moveTrack(Track* track, int indexTo);

	virtual void updateAfterTrackAdd();

	void clearAllTracks();

	const TrackList & tracks() const
	{
		return m_tracks;
	}

	bool isEmpty() const;

	static const QString classNodeName()
	{
		return "trackcontainer";
	}

	inline void setType( Type newType )
	{
		m_TrackContainerType = newType;
	}

	inline Type type() const
	{
		return m_TrackContainerType;
	}

	virtual AutomatedValueMap automatedValuesAt(TimePos time, int clipNum = -1) const;

signals:
	void trackAdded( noemixerr::Track * _track );
	void trackRemoved();
	void trackMoved();

protected:
	static AutomatedValueMap automatedValuesFromTracks(const TrackList &tracks, TimePos timeStart, int clipNum = -1);

	mutable QReadWriteLock m_tracksMutex;

private:
	TrackList m_tracks;

	Type m_TrackContainerType;


	friend class gui::TrackContainerView;
	friend class Track;

} ;

} // namespace noemixerr

#endif // NoeMixerr_TRACK_CONTAINER_H
