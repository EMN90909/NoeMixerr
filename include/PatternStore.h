// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PATTERN_STORE_H
#define NoeMixerr_PATTERN_STORE_H

#include "TrackContainer.h"
#include "ComboBoxModel.h"

namespace noemixerr
{

namespace gui
{
	class PatternEditorWindow;
}

/*
 * PatternStore is the backend of Pattern Editor:
 *
 * +----------------------------------+
 * | PatternStore (TrackContainer)    |
 * |                                  |
 * | +------------------------------+ |
 * | | Track 1   [Clip A]  [Clip B] | |
 * | +------------------------------+ |
 * |                                  |
 * | +------------------------------+ |
 * | | Track 2   [Clip C]  [Clip D] | |
 * | +------------------------------+ |
 * +----------------------------------+
 *
 * There is only one PatternStore which holds all patterns, and it's very similar to the Song Editor.
 * Think of it as a table - tracks are rows, bars are columns and clips are cells.
 * With this logic a "pattern" is a column, i.e. all clips on the same bar.
 * In the Pattern Editor you can select which pattern (column) you want to see, using the combo box at the top.
 * In the illustration above, Clip A and Clip C start on bar 1, thus they are "Pattern 1".
 *
 * Do not confuse tracks and clips in the PatternStore with PatternTracks and PatternClips.
 * - PatternTracks are used in the Song Editor. Each one reference a "pattern" in the PatternStore.
 * - PatternClips are stored inside PatternTracks. They are just empty placeholders.
 */
class NoeMixerr_EXPORT PatternStore : public TrackContainer
{
	Q_OBJECT
	mapPropertyFromModel(int, currentPattern, setCurrentPattern, m_patternComboBoxModel);
public:
	PatternStore();
	~PatternStore() override = default;

	virtual bool play(TimePos start, const f_cnt_t frames, const f_cnt_t frameBase, int clipNum = -1);

	void updateAfterTrackAdd() override;

	inline QString nodeName() const override
	{
		return "patternstore";
	}

	bar_t lengthOfPattern(int pattern) const;
	inline bar_t lengthOfCurrentPattern()
	{
		return lengthOfPattern(currentPattern());
	}
	int numOfPatterns() const;
	void removePattern(int pattern);

	void swapPattern(int p1, int p2);

	void updatePatternTrack(Clip* clip);
	void fixIncorrectPositions();
	void createClipsForPattern(int pattern);

	AutomatedValueMap automatedValuesAt(TimePos time, int clipNum) const override;

public slots:
	void play();
	void stop();
	void updateComboBox();

signals:
	void trackUpdated();

private:
	ComboBoxModel m_patternComboBoxModel;


	// Where the pattern selection combo box is
	friend class gui::PatternEditorWindow;

} ;


} // namespace noemixerr

#endif // NoeMixerr_PATTERN_STORE_H
