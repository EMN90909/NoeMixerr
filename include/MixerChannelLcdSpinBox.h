// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_MIXER_CHANNEL_LCD_SPIN_BOX_H
#define NoeMixerr_GUI_MIXER_CHANNEL_LCD_SPIN_BOX_H

#include "LcdSpinBox.h"

namespace noemixerr::gui
{


class TrackView;


class MixerChannelLcdSpinBox : public LcdSpinBox
{
	Q_OBJECT
public:
	MixerChannelLcdSpinBox(int numDigits, QWidget * parent, const QString& name, TrackView * tv = nullptr) :
		LcdSpinBox(numDigits, parent, name), m_tv(tv)
	{}
	~MixerChannelLcdSpinBox() override = default;

	void setTrackView(TrackView * tv);

protected:
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;

private:
	void enterValue();

	TrackView * m_tv;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_MIXER_CHANNEL_LCD_SPIN_BOX_H
