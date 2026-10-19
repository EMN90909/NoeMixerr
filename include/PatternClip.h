// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PATTERN_CLIP_H
#define NoeMixerr_PATTERN_CLIP_H

#include "Clip.h"

namespace noemixerr
{

/*! \brief Dummy clip for PatternTracks
 *
 *  Only used in the Song (Editor). See PatternStore.h for more info.
*/
class PatternClip : public Clip
{
public:
	PatternClip(Track* track);
	~PatternClip() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "patternclip";
	}

	int patternIndex();

	gui::ClipView * createView( gui::TrackView * _tv ) override;

	PatternClip* clone() override
	{
		return new PatternClip(*this);
	}

private:
	friend class PatternClipView;
} ;


} // namespace noemixerr

#endif // NoeMixerr_PATTERN_CLIP_H
