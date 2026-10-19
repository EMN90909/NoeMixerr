// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_FREQUENCY_SHIFTER_CONTROL_DIALOG_H
#define NoeMixerr_FREQUENCY_SHIFTER_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

#include <QTextEdit>

namespace noemixerr
{

class FrequencyShifterControls;

namespace gui
{

class FrequencyShifterControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	FrequencyShifterControlDialog(FrequencyShifterControls* c);
	~FrequencyShifterControlDialog() override = default;

public slots:
	void showHelpWindow();
};


class FrequencyShifterHelpView : public QTextEdit
{
	Q_OBJECT
public:
	static FrequencyShifterHelpView* getInstance()
	{
		static FrequencyShifterHelpView* instance = new FrequencyShifterHelpView;
		return instance;
	}

private:
	FrequencyShifterHelpView();
	static QString s_helpText;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_FREQUENCY_SHIFTER_CONTROL_DIALOG_H
