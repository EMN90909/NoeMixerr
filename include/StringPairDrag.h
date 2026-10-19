// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2007 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_STRING_PAIR_DRAG_H
#define NoeMixerr_GUI_STRING_PAIR_DRAG_H

#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include "noemixerr_export.h"

class QPixmap;

namespace noemixerr::gui
{


class NOEMIXERR_EXPORT StringPairDrag : public QDrag
{
public:
	StringPairDrag( const QString & _key, const QString & _value,
					const QPixmap & _icon, QWidget * _w );
	~StringPairDrag() override;

	static bool processDragEnterEvent( QDragEnterEvent * _dee,
						const QString & _allowed_keys );
	static QString decodeKey( QDropEvent * _de );
	static QString decodeValue( QDropEvent * _de );
} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_STRING_PAIR_DRAG_H
