// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SLEW_DISTORTION_CONTROL_DIALOG_H
#define NoeMixerr_GUI_SLEW_DISTORTION_CONTROL_DIALOG_H

#include "EffectControlDialog.h"
#include <QTextEdit>
#include <array>

namespace noemixerr
{

class SlewDistortionControls;
class FloatModel;

namespace gui
{

class Knob;

class SlewDistortionControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	SlewDistortionControlDialog(SlewDistortionControls* controls);
	~SlewDistortionControlDialog() override = default;
	
	void paintEvent(QPaintEvent* event) override;
public slots:
	void showHelpWindow();
private:
	SlewDistortionControls* m_controls;
	
	Knob* m_slewUp1Knob;
	Knob* m_slewUp2Knob;
	Knob* m_slewDown1Knob;
	Knob* m_slewDown2Knob;
	
	std::array<float, 4> m_lastInPeaks = {0};
	std::array<float, 4> m_lastOutPeaks = {0};
};

class SlewDistortionHelpView : public QTextEdit
{
	Q_OBJECT
public:
	static SlewDistortionHelpView* getInstance()
	{
		static SlewDistortionHelpView* instance = new SlewDistortionHelpView;
		return instance;
	}

private:
	SlewDistortionHelpView();
	static QString s_helpText;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_SLEW_DISTORTION_CONTROL_DIALOG_H
