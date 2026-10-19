// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Johannes Lorenz <j.git$$$lorenz-ho.me, $$$=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PLUGIN_ISSUE_H
#define NoeMixerr_PLUGIN_ISSUE_H

#include <QDebug>
#include <string>

namespace noemixerr
{

//! Types of issues that can cause NoeMixerr to not load a plugin
//! NoeMixerr Plugins should use this to indicate errors
enum class PluginIssueType
{
	// port flow & type
	UnknownPortFlow,
	UnknownPortType,
	// channel count
	TooManyInputChannels,
	TooManyOutputChannels,
	TooManyMidiInputChannels,
	TooManyMidiOutputChannels,
	NoOutputChannel,
	// port metadata
	PortHasNoDef,
	PortHasNoMin,
	PortHasNoMax,
	MinGreaterMax,
	DefaultValueNotInRange,
	LogScaleMinMissing,
	LogScaleMaxMissing,
	LogScaleMinMaxDifferentSigns,
	// features
	FeatureNotSupported, //!< plugin requires functionality NoeMixerr can't offer
	// misc
	BadPortType, //!< port type not supported
	Blocked,
	NoIssue
};

//! Issue type bundled with informational string
class PluginIssue
{
	static const char* msgFor(const PluginIssueType& it);

	PluginIssueType m_issueType;
	std::string m_info;

public:
	PluginIssue(PluginIssueType it, std::string msg = std::string())
		: m_issueType(it), m_info(msg)
	{
	}
	PluginIssueType type() const { return m_issueType; }
	bool operator==(const PluginIssue& other) const;
	bool operator<(const PluginIssue& other) const;
	friend QDebug operator<<(QDebug stream, const PluginIssue& iss);
};

QDebug operator<<(QDebug stream, const PluginIssue& iss);

} // namespace noemixerr

#endif // NoeMixerr_PLUGIN_ISSUE_H
