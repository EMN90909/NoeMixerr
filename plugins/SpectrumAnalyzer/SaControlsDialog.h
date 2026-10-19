// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef SACONTROLSDIALOG_H
#define SACONTROLSDIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{
class SaControls;
class SaProcessor;
}


namespace noemixerr::gui
{

class SaSpectrumView;
class SaWaterfallView;

//! Top-level widget holding the configuration GUI and spectrum displays
class SaControlsDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	explicit SaControlsDialog(SaControls *controls, SaProcessor *processor);
	~SaControlsDialog() override = default;

	QSize sizeHint() const override;

private:
	SaControls *m_controls;
	SaProcessor *m_processor;

	// Pointers to created widgets are needed to keep track of their sizeHint() changes.
	// Config widget is a plain QWidget so it has just a fixed height instead.
	const int m_configHeight = 75;
	SaSpectrumView *m_spectrum;
	SaWaterfallView *m_waterfall;
};


} // namespace noemixerr::gui

#endif // SACONTROLSDIALOG_H
