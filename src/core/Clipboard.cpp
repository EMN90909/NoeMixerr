// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QApplication>
#include <QClipboard>
#include <QMimeData>

#include "Clipboard.h"


namespace noemixerr::Clipboard
{

	const QMimeData * getMimeData()
	{
		return QApplication::clipboard()->mimeData( QClipboard::Clipboard );
	}




	bool hasFormat( MimeType mT )
	{
		return getMimeData()->hasFormat( mimeType( mT ) );
	}




	void copyString( const QString & str, MimeType mT )
	{
		auto content = new QMimeData;

		content->setData( mimeType( mT ), str.toUtf8() );
		QApplication::clipboard()->setMimeData( content, QClipboard::Clipboard );
	}




	QString getString( MimeType mT )
	{
		return QString( getMimeData()->data( mimeType( mT ) ) );
	}




	void copyStringPair( const QString & key, const QString & value )
	{
		QString finalString = key + ":" + value;

		auto content = new QMimeData;
		content->setData( mimeType( MimeType::StringPair ), finalString.toUtf8() );
		QApplication::clipboard()->setMimeData( content, QClipboard::Clipboard );
	}




	QString decodeKey( const QMimeData * mimeData )
	{
		return( QString::fromUtf8( mimeData->data( mimeType( MimeType::StringPair ) ) ).section( ':', 0, 0 ) );
	}




	QString decodeValue( const QMimeData * mimeData )
	{
		return( QString::fromUtf8( mimeData->data( mimeType( MimeType::StringPair ) ) ).section( ':', 1, -1 ) );
	}


} // namespace noemixerr::Clipboard
