// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "VecControlsDialog.h"


#include <QHBoxLayout>
#include <QVBoxLayout>

#include "LedCheckBox.h"
#include "VecControls.h"
#include "Vectorscope.h"
#include "VectorView.h"

namespace noemixerr::gui
{


// The entire GUI layout is built here.
VecControlsDialog::VecControlsDialog(VecControls *controls) :
	EffectControlDialog(controls),
	m_controls(controls)
{
	auto master_layout = new QVBoxLayout;
	master_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(master_layout);

	// Visualizer widget
	auto display = new VectorView(controls, m_controls->m_effect->getBuffer(), this);
	master_layout->addWidget(display);

	auto controlLayout = new QHBoxLayout();
	master_layout->addLayout(controlLayout);

	// Log. scale switch
	auto logarithmicButton = new LedCheckBox(tr("Log. scale"), this);
	logarithmicButton->setToolTip(tr("Display amplitude on logarithmic scale to better see small values."));
	logarithmicButton->setCheckable(true);
	logarithmicButton->setModel(&controls->m_logarithmicModel);
	controlLayout->addWidget(logarithmicButton);

	controlLayout->addStretch();

	// Switch between lines mode and point mode
	auto linesMode = new LedCheckBox(tr("Lines"), this);
	linesMode->setToolTip(tr("Render with lines."));
	linesMode->setCheckable(true);
	linesMode->setModel(&controls->m_linesModeModel);
	controlLayout->addWidget(linesMode);
}


// Suggest the best widget size.
QSize VecControlsDialog::sizeHint() const
{
	return QSize(275, 300);
}

} // namespace noemixerr::gui