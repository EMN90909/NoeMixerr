// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TRACK_CONTAINER_VIEW_H
#define NoeMixerr_GUI_TRACK_CONTAINER_VIEW_H

#include <QVector>
#include <QScrollArea>
#include <QWidget>
#include <QThread>

#include "JournallingObject.h"
#include "ModelView.h"
#include "Rubberband.h"
#include "TimePos.h"


class QVBoxLayout;

namespace noemixerr
{

class InstrumentTrack;
class Track;
class TrackContainer;

class InstrumentLoaderThread : public QThread
{
Q_OBJECT
public:
	InstrumentLoaderThread( QObject *parent = 0, InstrumentTrack *it = 0,
		QString name = "" );

	void run() override;

private:
	InstrumentTrack *m_it;
	QString m_name;
	QThread *m_containerThread;
};

namespace gui
{

class TrackView;

class TrackContainerView : public QWidget, public ModelView,
						public JournallingObject,
						public SerializingObjectHook
{
	Q_OBJECT
public:
	TrackContainerView( TrackContainer* tc );
	~TrackContainerView() override;

	void saveSettings( QDomDocument & _doc, QDomElement & _this ) override;
	void loadSettings( const QDomElement & _this ) override;

	QScrollArea * contentWidget()
	{
		return m_scrollArea;
	}

	inline const TimePos & currentPosition() const
	{
		return m_currentPosition;
	}

	virtual bool fixedClips() const
	{
		return false;
	}

	inline float pixelsPerBar() const
	{
		return m_ppb;
	}

	void setPixelsPerBar( int ppb );

	const TrackView * trackViewAt( const int _y ) const;

	virtual bool allowRubberband() const;
	virtual bool knifeMode() const;

	inline bool rubberBandActive() const
	{
		return m_rubberBand->isEnabled() && m_rubberBand->isVisible();
	}

	inline QVector<selectableObject *> selectedObjects()
	{
		return m_rubberBand->selectedObjects();
	}


	TrackContainer* model()
	{
		return m_tc;
	}

	const TrackContainer* model() const
	{
		return m_tc;
	}

	const QList<TrackView *> & trackViews() const
	{
		return( m_trackViews );
	}

	void moveTrackView( TrackView * trackView, int indexTo );
	void moveTrackViewUp( TrackView * trackView );
	void moveTrackViewDown( TrackView * trackView );
	void scrollToTrackView( TrackView * _tv );

	// -- for usage by trackView only ---------------
	TrackView * addTrackView( TrackView * _tv );
	void removeTrackView( TrackView * _tv );
	// -------------------------------------------------------

	void clearAllTracks();

	QString nodeName() const override
	{
		return "trackcontainerview";
	}

	unsigned int totalHeightOfTracks() const;

	RubberBand *rubberBand() const;

public slots:
	void realignTracks();
	noemixerr::gui::TrackView * createTrackView( noemixerr::Track * _t );
	void deleteTrackView( noemixerr::gui::TrackView * _tv );

	void dropEvent( QDropEvent * _de ) override;
	void dragEnterEvent( QDragEnterEvent * _dee ) override;

	///
	/// \brief stopRubberBand
	/// Removes the rubber band from display when finished with.
	void stopRubberBand();


protected:
	static const int DEFAULT_PIXELS_PER_BAR = 128;

	TimePos m_currentPosition;


private:
	class scrollArea : public QScrollArea
	{
	public:
		scrollArea( TrackContainerView* parent );
		~scrollArea() override = default;

	protected:
		void wheelEvent( QWheelEvent * _we ) override;

	private:
		TrackContainerView* m_trackContainerView;

	} ;
	friend class TrackContainerView::scrollArea;

	TrackContainer* m_tc;
	using trackViewList = QList<TrackView*>;
	trackViewList m_trackViews;

	scrollArea * m_scrollArea;
	QVBoxLayout * m_scrollLayout;

	float m_ppb;

	RubberBand * m_rubberBand;

signals:
	void positionChanged( const noemixerr::TimePos & _pos );
	void tracksRealigned();


} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_TRACK_CONTAINER_VIEW_H
