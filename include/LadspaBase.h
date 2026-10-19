// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LADSPA_BASE_H
#define NoeMixerr_LADSPA_BASE_H

#include <QRegularExpression>

#include "LadspaManager.h"
#include "Plugin.h"

namespace noemixerr
{


class LadspaControl;

enum class BufferRate {
	ChannelIn,
	ChannelOut,
	AudioRateInput,
	AudioRateOutput,
	ControlRateInput,
	ControlRateOutput
};

enum class BufferDataType { Toggled, Enum, Integer, Floating, Time, None };

//! This struct is used to hold port descriptions internally
//! which where received from the ladspa plugin
struct port_desc_t
{
	QString name;
	ch_cnt_t proc;
	uint16_t port_id;
	uint16_t control_id;
	BufferRate rate;
	BufferDataType data_type;
	float scale;
	LADSPA_Data max;
	LADSPA_Data min;
	LADSPA_Data def;
	LADSPA_Data value;
	//! This is true iff ladspa suggests logscale
	//! Note however that the model can still decide to use a linear scale
	bool suggests_logscale;
	LADSPA_Data* buffer;
	LadspaControl* control;
};

inline Plugin::Descriptor::SubPluginFeatures::Key ladspaKeyToSubPluginKey(
						const Plugin::Descriptor * _desc,
						const QString & _name,
						const ladspa_key_t & _key )
{
	Plugin::Descriptor::SubPluginFeatures::Key::AttributeMap m;
	QString file = _key.first;
	m["file"] = file.remove(QRegularExpression("\\.so$")).remove(QRegularExpression("\\.dll$"));
	m["plugin"] = _key.second;
	return Plugin::Descriptor::SubPluginFeatures::Key( _desc, _name, m );
}


} // namespace noemixerr

#endif // NoeMixerr_LADSPA_BASE_H
