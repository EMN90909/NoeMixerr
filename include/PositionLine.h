// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_POSITION_LINE_H
#define NoeMixerr_GUI_POSITION_LINE_H

#include <QWidget>

#include "Song.h"

namespace noemixerr::gui
{

class PositionLine : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(bool tailGradient MEMBER m_hasTailGradient)
	Q_PROPERTY(QColor lineColor MEMBER m_lineColor)
	Q_PROPERTY(QColor recordingColor MEMBER m_recordingColor)
public:
	PositionLine(QWidget* parent, Song::PlayMode playMode);

	bool isRecording() const { return m_isRecording; }

	void setRecording(bool recording);

public slots:
	void zoomChange(float zoom);

private:
	void paintEvent(QPaintEvent* pe) override;

	Song::PlayMode m_playMode;
	bool m_isRecording = false;

	bool m_hasTailGradient;
	QColor m_lineColor;
	QColor m_recordingColor;
};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_POSITION_LINE_H
