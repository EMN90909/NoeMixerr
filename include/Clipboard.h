// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_CLIPBOARD_H
#define NoeMixerr_CLIPBOARD_H

#include <QDomElement>
#include <QMap>

#include "noemixerr_export.h"

class QMimeData;

namespace noemixerr::Clipboard
{

	enum class MimeType
	{
		StringPair,
		Default
	};

	// Convenience Methods
	const QMimeData * getMimeData();
	bool hasFormat( MimeType mT );

	// Helper methods for String data
	void NoeMixerr_EXPORT copyString(const QString& str, MimeType mT);
	QString getString( MimeType mT );

	// Helper methods for String Pair data
	void copyStringPair( const QString & key, const QString & value );
	QString decodeKey( const QMimeData * mimeData );
	QString decodeValue( const QMimeData * mimeData );

	inline const char * mimeType( MimeType type )
	{
		switch( type )
		{
			case MimeType::StringPair:
				return "application/x-noemixerr-stringpair";
			break;
			case MimeType::Default:
			default:
				return "application/x-noemixerr-clipboard";
				break;
		}
	}

} // namespace noemixerr::Clipboard

#endif // NoeMixerr_CLIPBOARD_H
