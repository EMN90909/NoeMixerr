// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "VecControls.h"


#include "VecControlsDialog.h"
#include "Vectorscope.h"

namespace noemixerr
{


VecControls::VecControls(Vectorscope *effect) :
	EffectControls(effect),
	m_effect(effect),

	// initialize models and set default values
	m_logarithmicModel(false, this, tr("Logarithmic scale")),
	m_linesModeModel(true, this, tr("Lines rendering"))
{
}


// Create the VecControlDialog widget which handles display of GUI elements.
gui::EffectControlDialog* VecControls::createView()
{
	return new gui::VecControlsDialog(this);
}


void VecControls::loadSettings(const QDomElement &element)
{
	m_logarithmicModel.loadSettings(element, "Logarithmic");
	m_linesModeModel.loadSettings(element, "LinesMode");
}


void VecControls::saveSettings(QDomDocument &document, QDomElement &element)
{
	m_logarithmicModel.saveSettings(document, element, "Logarithmic");
	m_linesModeModel.saveSettings(document, element, "LinesMode");
}


} // namespace noemixerr
