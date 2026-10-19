// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "ComboBoxModel.h"

#include <cassert>

namespace noemixerr
{

void ComboBoxModel::addItem(QString item, std::unique_ptr<PixmapLoader> loader)
{
	m_items.emplace_back(std::move(item), std::move(loader));
	setRange( 0, m_items.size() - 1 );
}


void ComboBoxModel::replaceItem(std::size_t index, QString item, std::unique_ptr<PixmapLoader> loader)
{
	assert(index < m_items.size());
	m_items[index] = Item(std::move(item), std::move(loader));
	emit propertiesChanged();
}


void ComboBoxModel::clear()
{
	setRange( 0, 0 );

	m_items.clear();

	emit propertiesChanged();
}




int ComboBoxModel::findText( const QString& txt ) const
{
	for( auto it = m_items.begin(); it != m_items.end(); ++it )
	{
		if( ( *it ).first == txt )
		{
			return it - m_items.begin();
		}
	}
	return -1; 
}


} // namespace noemixerr


