// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PRESET_PREVIEW_PLAY_HANDLE_H
#define NoeMixerr_PRESET_PREVIEW_PLAY_HANDLE_H

#include "NotePlayHandle.h"

namespace noemixerr
{


class DataFile;
class InstrumentTrack;
class PreviewTrackContainer;

class NoeMixerr_EXPORT PresetPreviewPlayHandle : public PlayHandle
{
public:
	PresetPreviewPlayHandle( const QString& presetFile, bool loadByPlugin = false, DataFile *dataFile = 0 );
	~PresetPreviewPlayHandle() override;

	inline bool affinityMatters() const override
	{
		return true;
	}

	void play( SampleFrame* buffer ) override;
	bool isFinished() const override;

	bool isFromTrack( const Track * _track ) const override;

	static void init();
	static void cleanup();
	static ConstNotePlayHandleList nphsOfInstrumentTrack( const InstrumentTrack* instrumentTrack );

	static bool isPreviewing();


private:
	static PreviewTrackContainer* s_previewTC;

	NotePlayHandle* m_previewNote;

} ;


} // namespace noemixerr

#endif // NoeMixerr_PRESET_PREVIEW_PLAY_HANDLE_H
