// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "base64.h"

#include <QBuffer>
#include <QDataStream>

#include "DeprecationHelper.h"

namespace noemixerr::base64
{


QVariant decode(const QString& b64, QMetaType::Type forceType)
{
	char * dst = nullptr;
	int dsize = 0;
	base64::decode(b64, &dst, &dsize);
	QByteArray ba( dst, dsize );
	QBuffer buf( &ba );
	buf.open( QBuffer::ReadOnly );
	QDataStream in( &buf );
	QVariant ret;
	in >> ret;
	if (forceType != QMetaType::UnknownType && typeId(ret) != forceType)
	{
		buf.reset();
		in.setVersion( QDataStream::Qt_3_3 );
		in >> ret;
	}
	delete[] dst;
	return( ret );
}


} // namespace noemixerr::base64
