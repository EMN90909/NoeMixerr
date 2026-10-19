// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _VST_SUBPLUGIN_FEATURES_H
#define _VST_SUBPLUGIN_FEATURES_H


#include "Plugin.h"

namespace noemixerr
{


class VstSubPluginFeatures : public Plugin::Descriptor::SubPluginFeatures
{
public:
	VstSubPluginFeatures( Plugin::Type _type );

	void fillDescriptionWidget( QWidget * _parent,
											const Key * _key ) const override;

	void listSubPluginKeys( const Plugin::Descriptor * _desc,
											KeyList & _kl ) const override;
private:
	void addPluginsFromDir(QStringList* filenames,  QString path) const;
} ;


} // namespace noemixerr

#endif

