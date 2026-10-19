// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2011 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "Rubberband.h"

namespace noemixerr::gui
{


RubberBand::RubberBand( QWidget * _parent ) :
	QRubberBand( Rectangle, _parent )
{
}




QVector<selectableObject *> RubberBand::selectedObjects() const
{
	QVector<selectableObject *> so = selectableObjects();
	for( QVector<selectableObject *>::iterator it = so.begin();
							it != so.end(); )
	{
		if( ( *it )->isSelected() == false )
		{
			it = so.erase( it );
		}
		else
		{
			++it;
		}
	}
	return( so );
}




void RubberBand::resizeEvent( QResizeEvent * _re )
{
	QRubberBand::resizeEvent( _re );
}




QVector<selectableObject *> RubberBand::selectableObjects() const
{
	QVector<selectableObject *> so;
	if( parentWidget() == nullptr )
	{
		return( so );
	}

	QList<selectableObject *> l =
			parentWidget()->findChildren<selectableObject *>();
	for (const auto& obj : l)
	{
		so.push_back(obj);
	}
	return( so );
}


} // namespace noemixerr::gui
