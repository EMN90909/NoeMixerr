// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

#ifndef EQSPECTRUMVIEW_H
#define EQSPECTRUMVIEW_H

#include <QPainterPath>
#include <QWidget>

#include "fft_helpers.h"
#include "NoeMixerrTypes.h"

namespace noemixerr
{

class SampleFrame;

const int MAX_BANDS = 2048;
class EqAnalyser
{
public:
	EqAnalyser();
	virtual ~EqAnalyser();

	float m_bands[MAX_BANDS];
	bool getInProgress();
	void clear();

	void analyze( SampleFrame* buf, const f_cnt_t frames );

	float getEnergy() const;
	int getSampleRate() const;
	bool getActive() const;

	void setActive(bool active);

private:
	fftwf_plan m_fftPlan;
	fftwf_complex * m_specBuf;
	float m_absSpecBuf[FFT_BUFFER_SIZE+1];
	float m_buffer[FFT_BUFFER_SIZE*2];
	int m_framesFilledUp;
	float m_energy;
	int m_sampleRate;
	bool m_active;
	bool m_inProgress;
	float m_fftWindow[FFT_BUFFER_SIZE];
};


namespace gui
{

class EqSpectrumView : public QWidget
{
	Q_OBJECT
public:
	explicit EqSpectrumView( EqAnalyser *b, QWidget *_parent = 0 );
	~EqSpectrumView() override = default;

	QColor getColor() const;
	void setColor( const QColor &value );

protected:
	void paintEvent( QPaintEvent *event ) override;

private slots:
	void periodicalUpdate();

private:
	QColor m_color;
	EqAnalyser *m_analyser;
	QPainterPath m_path;
	float m_peakSum;
	float m_pixelsPerUnitWidth;
	float m_scale;
	int m_skipBands;
	bool m_periodicalUpdate;
	QList<float> m_bandHeight;

	float bandToFreq ( int index );
};


} // namespace gui

} // namespace noemixerr

#endif // EQSPECTRUMVIEW_H
