// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Lost Robot <r94231/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "DispersionControls.h"
#include "Dispersion.h"


namespace noemixerr
{

DispersionControls::DispersionControls(DispersionEffect* effect) :
	EffectControls(effect),
	m_effect(effect),
	m_amountModel(0, 0, MAX_DISPERSION_FILTERS, this, tr("Amount")),
	m_freqModel(200, 20, 20000, 0.001f, this, tr("Frequency")),
	m_resoModel(0.707f, 0.01f, 8, 0.0001f, this, tr("Resonance")),
	m_feedbackModel(0.f, -1.f, 1.f, 0.0001f, this, tr("Feedback")),
	m_dcModel(false, this, tr("DC Offset Removal"))
{
	m_freqModel.setScaleLogarithmic(true);
	m_resoModel.setScaleLogarithmic(true);
}



void DispersionControls::loadSettings(const QDomElement& parent)
{
	m_amountModel.loadSettings(parent, "amount");
	m_freqModel.loadSettings(parent, "freq");
	m_resoModel.loadSettings(parent, "reso");
	m_feedbackModel.loadSettings(parent, "feedback");
	m_dcModel.loadSettings(parent, "dc");
}




void DispersionControls::saveSettings(QDomDocument& doc, QDomElement& parent)
{
	m_amountModel.saveSettings(doc, parent, "amount");
	m_freqModel.saveSettings(doc, parent, "freq");
	m_resoModel.saveSettings(doc, parent, "reso");
	m_feedbackModel.saveSettings(doc, parent, "feedback");
	m_dcModel.saveSettings(doc, parent, "dc");
}


} // namespace noemixerr


