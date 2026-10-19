// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_COMBOBOX_MODEL_H
#define NoeMixerr_COMBOBOX_MODEL_H

#include <memory>
#include <utility>
#include <vector>

#include "AutomatableModel.h"
#include "embed.h"

namespace noemixerr
{

class NOEMIXERR_EXPORT ComboBoxModel : public IntModel
{
	Q_OBJECT
	MODEL_IS_VISITABLE
public:
	ComboBoxModel( Model* parent = nullptr,
					const QString& displayName = QString(),
					bool isDefaultConstructed = false ) :
		IntModel( 0, 0, 0, parent, displayName, isDefaultConstructed )
	{
		setJournalling(false);
	}

	void addItem( QString item, std::unique_ptr<PixmapLoader> loader = nullptr );

	void replaceItem(std::size_t index, QString item, std::unique_ptr<PixmapLoader> loader = nullptr);

	void clear();

	int findText( const QString& txt ) const;

	QString currentText() const
	{
		return ( size() > 0 && value() < size() ) ? m_items[value()].first : QString();
	}

	const PixmapLoader* currentData() const
	{
		return m_items[value()].second.get();
	}

	const QString & itemText( int i ) const
	{
		return m_items[std::clamp(i, minValue(), maxValue())].first;
	}

	const PixmapLoader* itemPixmap( int i ) const
	{
		return m_items[std::clamp(i, minValue(), maxValue())].second.get();
	}

	int size() const
	{
		return m_items.size();
	}


private:
	using Item = std::pair<QString, std::unique_ptr<PixmapLoader>>;

	std::vector<Item> m_items;

} ;

} // namespace noemixerr

#endif // NoeMixerr_COMBOBOX_MODEL_H
