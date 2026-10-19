// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LFO_CONTROLLER_H
#define NoeMixerr_LFO_CONTROLLER_H


#include "AutomatableModel.h"
#include "Controller.h"
#include "ControllerDialog.h"
#include "SampleBuffer.h"
#include "TempoSyncKnobModel.h"

namespace noemixerr
{

namespace gui
{

class AutomatableButtonGroup;
class PixmapButton;
class Knob;
class TempoSyncKnob;

class LfoControllerDialog;

}


class LfoController : public Controller
{
	Q_OBJECT
public:
	LfoController( Model * _parent );

	~LfoController() override;

	void saveSettings( QDomDocument & _doc, QDomElement & _this ) override;
	void loadSettings( const QDomElement & _this ) override;
	QString nodeName() const override;


public slots:
	gui::ControllerDialog * createDialog( QWidget * _parent ) override;


protected:
	// The internal per-controller value updating function
	void updateValueBuffer() override;

	FloatModel m_baseModel;
	TempoSyncKnobModel m_speedModel;
	FloatModel m_amountModel;
	FloatModel m_phaseModel;
	IntModel m_waveModel;
	IntModel m_multiplierModel;

	float m_duration;
	float m_phaseOffset;
	float m_currentPhase;

	sample_t (*m_sampleFunction)( const float );

private:
	float m_heldSample;
	std::shared_ptr<const SampleBuffer> m_userDefSampleBuffer = SampleBuffer::emptyBuffer();

protected slots:
	void updatePhase();
	void updateSampleFunction();
	void updateDuration();

	friend class gui::LfoControllerDialog;

} ;

namespace gui
{

class LfoControllerDialog : public ControllerDialog
{
	Q_OBJECT
public:
	LfoControllerDialog( Controller * _controller, QWidget * _parent );
	~LfoControllerDialog() override;


protected:
	void contextMenuEvent( QContextMenuEvent * _me ) override;
	void modelChanged() override;

	LfoController * m_lfo;

	Knob * m_baseKnob;
	TempoSyncKnob * m_speedKnob;
	Knob * m_amountKnob;
	Knob * m_phaseKnob;
	PixmapButton * m_userLfoBtn;
	AutomatableButtonGroup * m_waveBtnGrp;
	AutomatableButtonGroup * m_multiplierBtnGrp;


private:
	PixmapButton * m_userWaveBtn;

private slots:
	void askUserDefWave();

} ;


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_LFO_CONTROLLER_H
