// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LV2_SUBPLUGIN_FEATURES_H
#define NoeMixerr_LV2_SUBPLUGIN_FEATURES_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_LV2

#include <lilv/lilv.h>

#include "noemixerr_export.h"
#include "Plugin.h"

namespace noemixerr
{


class NOEMIXERR_EXPORT Lv2SubPluginFeatures : public Plugin::Descriptor::SubPluginFeatures
{
private:
	static const LilvPlugin *getPlugin(const Key &k);
	static QString pluginName(const LilvPlugin *plug);

public:
	Lv2SubPluginFeatures(Plugin::Type type);

	void fillDescriptionWidget(
		QWidget *parent, const Key *k) const override;

	QString additionalFileExtensions(const Key &k) const override;
	QString displayName(const Key &k) const override;
	QString description(const Key &k) const override;
	const PixmapLoader *logo(const Key &k) const override;

	void listSubPluginKeys(
		const Plugin::Descriptor *desc, KeyList &kl) const override;
};


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

#endif // NoeMixerr_LV2_SUBPLUGIN_FEATURES_H
