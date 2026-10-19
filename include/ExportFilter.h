// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NOEMIXERR_EXPORT_FILTER_H
#define NOEMIXERR_EXPORT_FILTER_H

#include <filesystem>

#include "TrackContainer.h"
#include "Plugin.h"


namespace noemixerr
{


class NOEMIXERR_EXPORT ExportFilter : public Plugin
{
public:
	ExportFilter( const Descriptor * _descriptor ) : Plugin( _descriptor, nullptr ) {}
	~ExportFilter() override = default;

	//! @brief Exports the project to a file
	//! @param tracks Song tracks
	//! @param patternStoreTracks PatternStore tracks
	//! @param tempo Song global tempo
	//! @param masterPitch Song master pitch
	//! @param filePath The path of the exported file
	//! @return If operation was successful
	virtual bool tryExport(const TrackContainer::TrackList& tracks,
		const TrackContainer::TrackList& patternTracks,
		int tempo, int masterPitch, const std::filesystem::path& filePath) = 0;

protected:

	void saveSettings( QDomDocument &, QDomElement & ) override
	{
	}

	void loadSettings( const QDomElement & ) override
	{
	}

	QString nodeName() const override
	{
		return "import_filter";
	}


private:

} ;


} // namespace noemixerr

#endif // NOEMIXERR_EXPORT_FILTER_H
