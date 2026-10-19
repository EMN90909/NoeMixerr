// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_BASE64_H
#define NoeMixerr_BASE64_H

#include <QByteArray>
#include <QMetaType>
#include <QString>
#include <QVariant>

namespace noemixerr::base64
{

	inline void encode( const char * _data, const int _size,
								QString & _dst )
	{
		_dst = QByteArray( _data, _size ).toBase64();
	}

	template<class T>
	inline void decode( const QString & _b64, T * * _data, int * _size )
	{
		QByteArray data = QByteArray::fromBase64( _b64.toUtf8() );
		*_size = data.size();
		*_data = new T[*_size / sizeof(T)];
		memcpy( *_data, data.constData(), *_size );
	}

	// for compatibility-code only
	QVariant decode(const QString& b64,
		QMetaType::Type forceType = QMetaType::UnknownType);

} // namespace noemixerr::base64

#endif // NoeMixerr_BASE64_H
