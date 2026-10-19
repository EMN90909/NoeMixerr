// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_PATTERN_EDITOR_H
#define NoeMixerr_GUI_PATTERN_EDITOR_H

#include "Editor.h"
#include "TrackContainerView.h"

namespace noemixerr
{

class PatternStore;

namespace gui
{

class ComboBox;
class TimeLineWidget;


class PatternEditor : public TrackContainerView
{
	Q_OBJECT
public:
	PatternEditor(PatternStore* ps);

	bool fixedClips() const override
	{
		return true;
	}

	void removeViewsForPattern(int pattern);

	void saveSettings(QDomDocument& doc, QDomElement& element) override;
	void loadSettings(const QDomElement& element) override;

public slots:
	void addSteps();
	void cloneSteps();
	void removeSteps();
	void addSampleTrack();
	void addAutomationTrack();
	void cloneClip();
	void updateMaxSteps();

protected slots:
	void dropEvent(QDropEvent * de ) override;
	void resizeEvent(QResizeEvent* de) override;
	void updatePosition();
	void updatePixelsPerBar();

private:
	PatternStore* m_ps;
	TimeLineWidget* m_timeLine;
	int m_trackHeadWidth;
	tick_t m_maxClipLength;
	void makeSteps( bool clone );
};


class PatternEditorWindow : public Editor
{
Q_OBJECT
public:
	PatternEditorWindow(PatternStore* ps);
	~PatternEditorWindow() = default;

	QSize sizeHint() const override;

	PatternEditor* m_editor;

public slots:
	void play() override;
	void stop() override;

private:
	ComboBox* m_patternComboBox;
};


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_PATTERN_EDITOR_H
