// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2006-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LADSPA_SUBPLUGIN_FEATURES_H
#define LADSPA_SUBPLUGIN_FEATURES_H

#include "LadspaManager.h"
#include "Plugin.h"

namespace noemixerr
{


class LadspaSubPluginFeatures : public Plugin::Descriptor::SubPluginFeatures
{
public:
	LadspaSubPluginFeatures( Plugin::Type _type );

	QString displayName(const Key& k) const override;
	void fillDescriptionWidget( QWidget * _parent,
												const Key * _key ) const override;

	void listSubPluginKeys( const Plugin::Descriptor * _desc,
												KeyList & _kl ) const override;


	static ladspa_key_t subPluginKeyToLadspaKey( const Key * _key );

};


} // namespace noemixerr

#endif
