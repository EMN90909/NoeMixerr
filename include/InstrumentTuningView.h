// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2020-2022 Martin Pavelek <he29.HS/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_INSTRUMENT_TUNING_VIEW_H
#define NoeMixerr_GUI_INSTRUMENT_TUNING_VIEW_H

#include <QWidget>

class QLabel;

namespace noemixerr
{

class InstrumentTrack;

namespace gui
{

class ComboBox;
class GroupBox;
class LedCheckBox;


class InstrumentTuningView : public QWidget
{
	Q_OBJECT
public:
	InstrumentTuningView(InstrumentTrack *it, QWidget *parent);

	GroupBox *pitchGroupBox() {return m_pitchGroupBox;}
	GroupBox *microtunerGroupBox() {return m_microtunerGroupBox;}

	QLabel *microtunerNotSupportedLabel() {return m_microtunerNotSupportedLabel;}

	ComboBox *scaleCombo() {return m_scaleCombo;}
	ComboBox *keymapCombo() {return m_keymapCombo;}

	LedCheckBox *rangeImportCheckbox() {return m_rangeImportCheckbox;}

private:
	GroupBox *m_pitchGroupBox;
	GroupBox *m_microtunerGroupBox;

	QLabel *m_microtunerNotSupportedLabel;

	ComboBox *m_scaleCombo;
	ComboBox *m_keymapCombo;

	LedCheckBox *m_rangeImportCheckbox;
};


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_INSTRUMENT_TUNING_VIEW_H
