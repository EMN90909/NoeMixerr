// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024- Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TRACK_GRIP_H
#define NoeMixerr_GUI_TRACK_GRIP_H

#include <QWidget>


class QPixmap;

namespace noemixerr
{

namespace gui
{

class TrackView;

class TrackGrip : public QWidget
{
	Q_OBJECT
public:
	TrackGrip(TrackView* trackView, QWidget* parent = nullptr);
	~TrackGrip() override = default;

signals:
	void grabbed();
	void released();

protected:
	void mousePressEvent(QMouseEvent*) override;
	void mouseReleaseEvent(QMouseEvent*) override;
	void paintEvent(QPaintEvent*) override;

private:
	TrackView* m_trackView = nullptr;
	bool m_isGrabbed = false;
	static QPixmap* s_grabbedPixmap;
	static QPixmap* s_releasedPixmap;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_TRACK_GRIP_H
