// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "AutomatableModel.h"
#include "DelayControlsDialog.h"
#include "DelayControls.h"
#include "DeprecationHelper.h"
#include "embed.h"
#include "TempoSyncKnob.h"
#include "../Eq/EqFader.h"
#include <QMouseEvent>
#include <QPainter>

namespace noemixerr::gui
{


DelayControlsDialog::DelayControlsDialog( DelayControls *controls ) :
	EffectControlDialog( controls )
{
	setAutoFillBackground( true );
	QPalette pal;
	pal.setBrush( backgroundRole(), PLUGIN_NAME::getIconPixmap( "artwork" ) );
	setPalette( pal );
	setFixedSize( 300, 208 );

	auto sampleDelayKnob = new TempoSyncKnob(KnobType::Bright26, tr("DELAY"), this, Knob::LabelRendering::LegacyFixedFontSize);
	sampleDelayKnob->move( 10,14 );
	sampleDelayKnob->setModel( &controls->m_delayTimeModel );
	sampleDelayKnob->setHintText(tr("Delay time:"), " s");

	auto feedbackKnob = new VolumeKnob(KnobType::Bright26, tr("FDBK"), this, Knob::LabelRendering::LegacyFixedFontSize);
	feedbackKnob->move( 11, 58 );
	feedbackKnob->setZeroDbfsPoint(1.f);
	feedbackKnob->setModel( &controls->m_feedbackModel);
	feedbackKnob->setHintText(tr("Feedback amount:"), "");

	auto lfoFreqKnob = new TempoSyncKnob(KnobType::Bright26, tr("RATE"), this, Knob::LabelRendering::LegacyFixedFontSize);
	lfoFreqKnob->move( 11, 119 );
	lfoFreqKnob->setModel( &controls->m_lfoTimeModel );
	lfoFreqKnob->setHintText(tr("LFO frequency:"), " s");

	auto lfoAmtKnob = new TempoSyncKnob(KnobType::Bright26, tr("AMNT"), this, Knob::LabelRendering::LegacyFixedFontSize);
	lfoAmtKnob->move( 11, 159 );
	lfoAmtKnob->setModel( &controls->m_lfoAmountModel );
	lfoAmtKnob->setHintText(tr("LFO amount:"), " s");

	auto outFader
		= new EqFader(&controls->m_outGainModel, tr("Out gain"), this, &controls->m_outPeakL, &controls->m_outPeakR);
	outFader->setMaximumHeight( 196 );
	outFader->move( 263, 45 );
	outFader->setDisplayConversion( false );
	outFader->setHintText(tr("Gain:"), " dBFS");

	auto pad = new XyPad(this, &controls->m_feedbackModel, &controls->m_delayTimeModel);
	pad->resize( 200, 200 );
	pad->move( 50, 5 );
}




XyPad::XyPad(QWidget *parent, FloatModel *xModel, FloatModel *yModel) :
	QWidget( parent ),
	m_xModel( xModel ),
	m_yModel( yModel ),
	m_acceptInput( false )
{
	connect( m_xModel, SIGNAL( dataChanged() ) , this, SLOT( update() ) );
	connect( m_yModel, SIGNAL( dataChanged() ) , this, SLOT( update() ) );
}




void XyPad::paintEvent(QPaintEvent *event)
{
	QPainter painter( this );
		//Draw Frequecy maker lines
		painter.setPen( QPen( QColor( 200, 200, 200, 200 ), 8, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin ) );
		painter.setRenderHint( QPainter::Antialiasing, true );

		float xRange = m_xModel->maxValue() - m_xModel->minValue();
		float xInc = xRange / width();
		int xPos = ( m_xModel->value() - m_xModel->minValue() ) / xInc;

		float yRange = m_yModel->maxValue() - m_yModel->minValue();
		float yInc = yRange / height();
		int yPos = ( m_yModel->value() - m_yModel->minValue() ) / yInc;

		painter.drawPoint( xPos, yPos );
}




void XyPad::mousePressEvent(QMouseEvent *event)
{
	m_acceptInput = true;
}




void XyPad::mouseReleaseEvent(QMouseEvent *event)
{
	m_acceptInput = false;
}




void XyPad::mouseMoveEvent(QMouseEvent *event)
{
	const auto pos = position(event);

	if (m_acceptInput && (pos.x() >= 0) && (pos.x() < width())
		&& (pos.y() >= 0) && (pos.y() < height()))
	{
		//set xmodel
		float xRange = m_xModel->maxValue() - m_xModel->minValue();
		float xInc = xRange / width();
		m_xModel->setValue(m_xModel->minValue() + (pos.x() * xInc));

		//set ymodel
		float yRange = m_yModel->maxValue() - m_yModel->minValue();
		float yInc = yRange / height();
		m_yModel->setValue(m_yModel->minValue() + (pos.y() * yInc));
	}
}


} // namespace noemixerr::gui