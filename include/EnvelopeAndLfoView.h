// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_ENVELOPE_AND_LFO_VIEW_H
#define NoeMixerr_GUI_ENVELOPE_AND_LFO_VIEW_H

#include <QWidget>

#include "ModelView.h"

namespace noemixerr
{

class EnvelopeAndLfoParameters;

namespace gui
{

class AutomatableButtonGroup;
class Knob;
class LedCheckBox;
class PixmapButton;
class TempoSyncKnob;
class EnvelopeGraph;
class LfoGraph;



class EnvelopeAndLfoView : public QWidget, public ModelView
{
	Q_OBJECT
public:
	EnvelopeAndLfoView( QWidget * _parent );
	~EnvelopeAndLfoView() override;


protected:
	void modelChanged() override;

	void dragEnterEvent( QDragEnterEvent * _dee ) override;
	void dropEvent( QDropEvent * _de ) override;


protected slots:
	void lfoUserWaveChanged();


private:
	EnvelopeAndLfoParameters * m_params;

	// envelope stuff
	EnvelopeGraph* m_envelopeGraph;
	Knob * m_predelayKnob;
	Knob * m_attackKnob;
	Knob * m_holdKnob;
	Knob * m_decayKnob;
	Knob * m_sustainKnob;
	Knob * m_releaseKnob;
	Knob * m_amountKnob;

	// LFO stuff
	LfoGraph* m_lfoGraph;
	Knob * m_lfoPredelayKnob;
	Knob * m_lfoAttackKnob;
	TempoSyncKnob * m_lfoSpeedKnob;
	Knob * m_lfoAmountKnob;
	PixmapButton * m_userLfoBtn;
	AutomatableButtonGroup * m_lfoWaveBtnGrp;

	LedCheckBox * m_x100Cb;
	LedCheckBox * m_controlEnvAmountCb;
} ;

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_ENVELOPE_AND_LFO_VIEW_H
