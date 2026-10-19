// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <QMimeData>
#include <QDragEnterEvent>


#include "StringPairDrag.h"
#include "GuiApplication.h"
#include "MainWindow.h"
#include "Clipboard.h"


namespace noemixerr::gui
{


StringPairDrag::StringPairDrag( const QString & _key, const QString & _value,
					const QPixmap & _icon, QWidget * _w ) :
	QDrag( _w )
{
	// For mimeType() and MimeType enum class
	using namespace Clipboard;

	if( _icon.isNull() && _w )
	{
		setPixmap( _w->grab().scaled(
						64, 64,
						Qt::KeepAspectRatio,
						Qt::SmoothTransformation ) );
	}
	else
	{
		setPixmap( _icon );
	}
	QString txt = _key + ":" + _value;
	auto m = new QMimeData();
	m->setData( mimeType( MimeType::StringPair ), txt.toUtf8() );
	setMimeData( m );
	exec( Qt::CopyAction, Qt::CopyAction );
}




StringPairDrag::~StringPairDrag()
{
	// during a drag, we might have lost key-press-events, so reset
	// modifiers of main-win
	if( getGUI()->mainWindow() )
	{
		getGUI()->mainWindow()->clearKeyModifiers();
	}
}




bool StringPairDrag::processDragEnterEvent( QDragEnterEvent * _dee,
						const QString & _allowed_keys )
{
	// For mimeType() and MimeType enum class
	using namespace Clipboard;

	if( !_dee->mimeData()->hasFormat( mimeType( MimeType::StringPair ) ) )
	{
		return( false );
	}
	QString txt = _dee->mimeData()->data( mimeType( MimeType::StringPair ) );
	if( _allowed_keys.split( ',' ).contains( txt.section( ':', 0, 0 ) ) )
	{
		_dee->acceptProposedAction();
		return( true );
	}
	_dee->ignore();
	return( false );
}




QString StringPairDrag::decodeKey( QDropEvent * _de )
{
	return Clipboard::decodeKey( _de->mimeData() );
}




QString StringPairDrag::decodeValue( QDropEvent * _de )
{
	return Clipboard::decodeValue( _de->mimeData() );
}


} // namespace noemixerr::gui