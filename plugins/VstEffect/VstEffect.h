// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _VST_EFFECT_H
#define _VST_EFFECT_H

#include <QMutex>
#include <QSharedPointer>

#include "Effect.h"
#include "VstEffectControls.h"

namespace noemixerr
{


class VstPlugin;


class VstEffect : public Effect
{
public:
	VstEffect( Model * _parent,
			const Descriptor::SubPluginFeatures::Key * _key );
	~VstEffect() override = default;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls * controls() override
	{
		return &m_vstControls;
	}


private:
	//! Returns true if plugin was loaded (m_plugin != nullptr)
	bool openPlugin(const QString& plugin);
	void closePlugin();

	QSharedPointer<VstPlugin> m_plugin;
	QMutex m_pluginMutex;
	EffectKey m_key;

	VstEffectControls m_vstControls;


	friend class VstEffectControls;
	friend class gui::VstEffectControlDialog;
	friend class gui::ManageVSTEffectView;

} ;


} // namespace noemixerr

#endif
