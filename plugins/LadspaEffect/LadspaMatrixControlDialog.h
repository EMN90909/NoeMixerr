// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2015 Michael Gregorius <michaelgregorius/at/web[dot]de>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LADSPA_MATRIX_CONTROL_DIALOG_H
#define LADSPA_MATRIX_CONTROL_DIALOG_H

#include "EffectControlDialog.h"

#include "NoeMixerrTypes.h"


class QGridLayout;
class QScrollArea;

namespace noemixerr
{

class LadspaControls;

namespace gui
{

class LedCheckBox;


class LadspaMatrixControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	LadspaMatrixControlDialog(LadspaControls* ctl);

private slots:
	void updateEffectView(LadspaControls* ctl);

private:
	//! @brief Checks if a link column is needed for the current effect controls.
	//! @return true if a link column is needed.
	bool needsLinkColumn() const;

	//! @brief Arranges widgets for the current controls in a grid/matrix layout.
	//! @param parent The parent of all created widgets
	//! @param gridLayout The layout into which the controls are organized
	void arrangeControls(QWidget * parent, QGridLayout* gridLayout);

	//! @brief Creates a widget that holds the widgets of the current controls in a matrix arrangement.
	QWidget * createMatrixWidget();

	LadspaControls * getLadspaControls() const;
	ch_cnt_t getChannelCount() const;

private:
	QScrollArea* m_scrollArea;
	LedCheckBox* m_stereoLink;
};

} // namespace gui

} // namespace noemixerr

#endif
