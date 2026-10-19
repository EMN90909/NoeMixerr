// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

namespace noemixerr
{


struct VstParameterDumpItem
{
	int32_t index;
	std::string shortLabel;
	float value;
} ;



enum class VstHostLanguage
{
	English = 1,
	German,
	French,
	Italian,
	Spanish,
	Japanese,
	Korean
} ;



enum VstRemoteMessageIDs
{
	// vstPlugin -> remoteVstPlugin
	IdVstLoadPlugin = RemoteMessageIDs::IdUserBase,
	IdVstClosePlugin,
	IdVstSetTempo,
	IdVstSetLanguage,
	IdVstGetParameterCount,
	IdVstGetParameterDump,
	IdVstSetParameterDump,
	IdVstProgramNames,
	IdVstCurrentProgram,
	IdVstCurrentProgramName,
	IdVstSetProgram,
	IdVstRotateProgram,
	IdVstIdleUpdate,
	IdVstLoadAllParameterDisplays,
	IdVstLoadAllParameterLabels,
	IdVstUpdateParameterDisplay,
	IdVstUpdateParameterLabel,

	// remoteVstPlugin -> vstPlugin
	IdVstFailedLoadingPlugin,
	IdVstPluginWindowID,
	IdVstPluginEditorGeometry,
	IdVstPluginName,
	IdVstPluginVersion,
	IdVstPluginVendorString,
	IdVstPluginProductString,
	IdVstPluginPresetsString,
	IdVstPluginUniqueID,
	IdVstSetParameter,
	IdVstParameterCount,
	IdVstParameterDump

} ;


} // namespace noemixerr

#endif
