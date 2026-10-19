// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019-2020 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Lv2Basics.h"

#ifdef NoeMixerr_HAVE_LV2

namespace noemixerr
{

QString qStringFromPluginNode(const LilvPlugin* plug,
	LilvNode* (*getFunc)(const LilvPlugin*))
{
	return QString::fromUtf8(
		lilv_node_as_string(AutoLilvNode((*getFunc)(plug)).get()));
}

QString qStringFromPortName(const LilvPlugin* plug, const LilvPort* port)
{
	return QString::fromUtf8(
		lilv_node_as_string(AutoLilvNode(lilv_port_get_name(plug, port)).get()));
}

std::string stdStringFromPortName(const LilvPlugin* plug, const LilvPort* port)
{
	return std::string(
			lilv_node_as_string(AutoLilvNode(lilv_port_get_name(plug, port)).get()));
}

} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

