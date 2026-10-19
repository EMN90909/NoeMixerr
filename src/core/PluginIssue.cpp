// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019-2024 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QDebug>

#include "PluginIssue.h"

namespace noemixerr
{


const char *PluginIssue::msgFor(const PluginIssueType &it)
{
	switch (it)
	{
		case PluginIssueType::UnknownPortFlow:
			return "unknown port flow for mandatory port";
		case PluginIssueType::UnknownPortType:
			return "unknown port type for mandatory port";
		case PluginIssueType::TooManyInputChannels:
			return "too many audio input channels";
		case PluginIssueType::TooManyOutputChannels:
			return "too many audio output channels";
		case PluginIssueType::TooManyMidiInputChannels:
			return "too many MIDI input channels";
		case PluginIssueType::TooManyMidiOutputChannels:
			return "too many MIDI output channels";
		case PluginIssueType::NoOutputChannel:
			return "no audio output channel";
		case PluginIssueType::PortHasNoDef:
			return "port is missing default value";
		case PluginIssueType::PortHasNoMin:
			return "port is missing min value";
		case PluginIssueType::PortHasNoMax:
			return "port is missing max value";
		case PluginIssueType::MinGreaterMax:
			return "port minimum is greater than maximum";
		case PluginIssueType::DefaultValueNotInRange:
			return "default value is not in range [min, max]";
		case PluginIssueType::LogScaleMinMissing:
			return "logscale requires minimum value";
		case PluginIssueType::LogScaleMaxMissing:
			return "logscale requires maximum value";
		case PluginIssueType::LogScaleMinMaxDifferentSigns:
			return "logscale with min < 0 < max";
		case PluginIssueType::FeatureNotSupported:
			return "required feature not supported";
		case PluginIssueType::BadPortType:
			return "unsupported port type";
		case PluginIssueType::Blocked:
			return "blocked plugin";
		case PluginIssueType::NoIssue:
			return nullptr;
	}
	return nullptr;
}




bool PluginIssue::operator==(const PluginIssue &other) const
{
	return (m_issueType == other.m_issueType) && (m_info == other.m_info);
}




bool PluginIssue::operator<(const PluginIssue &other) const
{
	return (m_issueType != other.m_issueType)
			? m_issueType < other.m_issueType
			: m_info < other.m_info;
}


QDebug operator<<(QDebug stream, const PluginIssue &iss)
{
	stream << PluginIssue::msgFor(iss.m_issueType);
	if (iss.m_info.length())
	{
		stream.nospace() << ": " << iss.m_info.c_str();
	}
	return stream;
}

} // namespace noemixerr



