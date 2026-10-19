// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025-2026 Keratin
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QDomElement>

#include "Oscilloscope.h"
#include "OscilloscopeControls.h"
#include "OscilloscopeControlDialog.h"
#include "OscilloscopeGraph.h"

namespace noemixerr
{

OscilloscopeControls::OscilloscopeControls(Oscilloscope* effect) :
	EffectControls(effect),
	m_ampModel(100.0f, 0.0f, 1000.0f, 0.00001f, this, tr("Amplitude")),
	m_lengthModel(500.0f, 1.0f, gui::OscilloscopeGraph::MaxBufferLengthSeconds * 1000, 0.001f, this, tr("Length")),
	m_phaseModel(1.0f, 0.0f, 1.0f, 0.00001f, this, tr("Phase")),
	m_pauseModel(false, this, tr("Pause")),
	m_stereoModel(false, this, tr("Stereo")),
	m_effect(effect)
{
	m_lengthModel.setScaleLogarithmic(true);
}


void OscilloscopeControls::loadSettings(const QDomElement& parent)
{
	m_ampModel.loadSettings(parent, "amp");
	m_lengthModel.loadSettings(parent, "length");
	m_phaseModel.loadSettings(parent, "phase");
	m_stereoModel.loadSettings(parent, "stereo");
}


void OscilloscopeControls::saveSettings(QDomDocument& doc, QDomElement& parent)
{
	m_ampModel.saveSettings(doc, parent, "amp");
	m_lengthModel.saveSettings(doc, parent, "length");
	m_phaseModel.saveSettings(doc, parent, "phase");
	m_stereoModel.saveSettings(doc, parent, "stereo");
}


gui::EffectControlDialog* OscilloscopeControls::createView()
{
	return new gui::OscilloscopeControlDialog(this);
}


} // namespace noemixerr
