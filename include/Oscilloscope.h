// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_OSCILLOSCOPE_H
#define NoeMixerr_GUI_OSCILLOSCOPE_H

#include <QWidget>
#include <QPixmap>

#include "NoeMixerrTypes.h"

namespace noemixerr
{

class SampleFrame;

}

namespace noemixerr::gui
{


class Oscilloscope : public QWidget
{
	Q_OBJECT
public:
	Q_PROPERTY( QColor leftChannelColor READ leftChannelColor WRITE setLeftChannelColor )
	Q_PROPERTY( QColor rightChannelColor READ rightChannelColor WRITE setRightChannelColor )
	Q_PROPERTY( QColor otherChannelsColor READ otherChannelsColor WRITE setOtherChannelsColor )
	Q_PROPERTY( QColor clippingColor READ clippingColor WRITE setClippingColor )

	Oscilloscope( QWidget * _parent );
	~Oscilloscope() override;

	void setActive( bool _active );

	QColor const & leftChannelColor() const;
	void setLeftChannelColor(QColor const & leftChannelColor);

	QColor const & rightChannelColor() const;
	void setRightChannelColor(QColor const & rightChannelColor);

	QColor const & otherChannelsColor() const;
	void setOtherChannelsColor(QColor const & otherChannelsColor);

	QColor const & clippingColor() const;
	void setClippingColor(QColor const & clippingColor);


protected:
	void paintEvent( QPaintEvent * _pe ) override;
	void mousePressEvent( QMouseEvent * _me ) override;


protected slots:
	void updateAudioBuffer(const noemixerr::SampleFrame* buffer);

private:
	bool clips(float level) const;

private:
	QPixmap m_background;
	QPointF * m_points;

	SampleFrame* m_buffer;
	bool m_active;

	QColor m_leftChannelColor;
	QColor m_rightChannelColor;
	QColor m_otherChannelsColor;
	QColor m_clippingColor;
} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_OSCILLOSCOPE_H
