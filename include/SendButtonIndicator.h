// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014-2022 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SEND_BUTTON_INDICATOR_H
#define NoeMixerr_GUI_SEND_BUTTON_INDICATOR_H

#include <QLabel>
#include "embed.h"


namespace noemixerr
{

class FloatModel;

namespace gui
{

class MixerChannelView;
class MixerView;

class SendButtonIndicator : public QLabel
{
public:
	SendButtonIndicator(QWidget* parent, MixerChannelView* owner, MixerView* mv);

	void mousePressEvent(QMouseEvent* e) override;
	void updateLightStatus();

private:

	MixerChannelView* m_parent;
	MixerView* m_mv;
	QPixmap m_qpmOff = embed::getIconPixmap("mixer_send_off", 29, 20);
	QPixmap m_qpmOn = embed::getIconPixmap("mixer_send_on", 29, 20);

	FloatModel* getSendModel();
};


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_SEND_BUTTON_INDICATOR_H
