// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GRANULAR_PITCH_SHIFTER_CONTROLS_H
#define NoeMixerr_GRANULAR_PITCH_SHIFTER_CONTROLS_H

#include "EffectControlDialog.h"

#include <QTextEdit>

namespace noemixerr
{

class GranularPitchShifterControls;

namespace gui
{

class GranularPitchShifterControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	GranularPitchShifterControlDialog(GranularPitchShifterControls* controls);
	~GranularPitchShifterControlDialog() override = default;
public slots:
	void showHelpWindow();
};

class GranularPitchShifterHelpView : public QTextEdit
{
	Q_OBJECT
public:
	static GranularPitchShifterHelpView* getInstance()
	{
		static GranularPitchShifterHelpView instance;
		return &instance;
	}

private:
	GranularPitchShifterHelpView();
	static QString s_helpText;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GRANULAR_PITCH_SHIFTER_CONTROLS_H
