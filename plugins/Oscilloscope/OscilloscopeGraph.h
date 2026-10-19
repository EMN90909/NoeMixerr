// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025-2026 Keratin
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_OSCILLOSCOPE_GRAPH_H
#define NoeMixerr_GUI_OSCILLOSCOPE_GRAPH_H

#include "OscilloscopeControls.h"
#include "LocklessRingBuffer.h"
#include <QWidget>

namespace noemixerr
{

class OscilloscopeControls;
class FloatModel;

namespace gui
{

class Knob;

class OscilloscopeGraph : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QColor monoColor MEMBER m_monoColor)
	Q_PROPERTY(QColor leftColor MEMBER m_leftColor)
	Q_PROPERTY(QColor rightColor MEMBER m_rightColor)
	Q_PROPERTY(QColor minorLineColor MEMBER m_minorLineColor)
	Q_PROPERTY(QColor clippingLineColor MEMBER m_clippingLineColor)
	Q_PROPERTY(QColor backgroundColor MEMBER m_backgroundColor)
public:
	OscilloscopeGraph(QWidget* parent, OscilloscopeControls* controls);
	~OscilloscopeGraph() override = default;

	void paintEvent(QPaintEvent* pe) override;
	void wheelEvent(QWheelEvent* we) override;
	void mousePressEvent(QMouseEvent* me) override;
	void mouseMoveEvent(QMouseEvent* me) override;

	//! Maximum length of the oscilloscope history in seconds
	static constexpr float MaxBufferLengthSeconds = 5.0f;

private slots:
	void changeSampleRate();

private:
	OscilloscopeControls* m_controls;

	LocklessRingBufferReader<SampleFrame> m_inputBufferReader;

	// Buffer which is actually drawn on the screen, not the ring buffer used for communication between threads
	std::vector<SampleFrame> m_ringBuffer;
	int m_ringBufferIndex = 0;

	int m_mousePos;

	QColor m_monoColor = QColor(255, 255, 255);
	QColor m_leftColor = QColor(126, 146, 255, 128);
	QColor m_rightColor = QColor(255, 128, 128, 128);
	QColor m_minorLineColor = QColor(100, 100, 100);
	QColor m_clippingLineColor = QColor(100, 0, 0);
	QColor m_backgroundColor = QColor(0, 0, 0);
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_OSCILLOSCOPE_GRAPH_H
