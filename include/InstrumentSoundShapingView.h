// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_INSTRUMENT_SOUND_SHAPING_VIEW_H
#define NoeMixerr_GUI_INSTRUMENT_SOUND_SHAPING_VIEW_H

#include <QWidget>

#include "ModelView.h"

class QLabel;

namespace noemixerr { class InstrumentSoundShaping; }

namespace noemixerr::gui
{

class EnvelopeAndLfoView;
class ComboBox;
class GroupBox;
class Knob;
class TabWidget;


class InstrumentSoundShapingView : public QWidget, public ModelView
{
	Q_OBJECT
public:
	InstrumentSoundShapingView( QWidget * _parent );
	~InstrumentSoundShapingView() override;

	void setFunctionsHidden( bool hidden );


private:
	void modelChanged() override;


	InstrumentSoundShaping * m_ss = nullptr;
	TabWidget * m_targetsTabWidget;

	EnvelopeAndLfoView* m_volumeView;
	EnvelopeAndLfoView* m_cutoffView;
	EnvelopeAndLfoView* m_resonanceView;

	// filter-stuff
	GroupBox * m_filterGroupBox;
	ComboBox * m_filterComboBox;
	Knob * m_filterCutKnob;
	Knob * m_filterResKnob;

	QLabel* m_singleStreamInfoLabel;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_INSTRUMENT_SOUND_SHAPING_VIEW_H
