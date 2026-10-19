// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// Copyright (c) 2025- Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.

#ifndef VECTORVIEW_H
#define VECTORVIEW_H

#include <QWidget>

#include "LocklessRingBuffer.h"

namespace noemixerr
{
class VecControls;
class SampleFrame;
}

//#define VEC_DEBUG

namespace noemixerr::gui
{


// Widget that displays a vectorscope visualization of stereo signal.
class VectorView : public QWidget
{
	Q_OBJECT
public:
	VectorView(VecControls* controls, LocklessRingBuffer<SampleFrame>* inputBuffer, QWidget* parent = nullptr);
	~VectorView() override = default;

	QSize sizeHint() const override {return QSize(300, 300);}

	Q_PROPERTY(QColor colorTrace MEMBER m_colorTrace)
	Q_PROPERTY(QColor colorGrid MEMBER m_colorGrid)
	Q_PROPERTY(QColor colorLabels MEMBER m_colorLabels)

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

private slots:
	void periodicUpdate();

private:
	void drawZoomInfo();

private:
	VecControls *m_controls;

	LocklessRingBuffer<SampleFrame> *m_inputBuffer;
	LocklessRingBufferReader<SampleFrame> m_bufferReader;

	float m_zoom;

	// State variables for comparison with previous repaint
	unsigned int m_zoomTimestamp;

	QPointF m_lastPoint = QPoint();

	QColor m_colorTrace = QColor(60, 255, 130, 255);	// ~NoeMixerr green
	QColor m_colorGrid = QColor(76, 80, 84, 128);		// ~60 % gray (slightly cold / blue), 50 % transparent
	QColor m_colorLabels = QColor(76, 80, 84, 255);		// ~60 % gray (slightly cold / blue)

#ifdef VEC_DEBUG
	float m_executionAvg = 0;
#endif
};


} // namespace noemixerr::gui

#endif // VECTORVIEW_H
