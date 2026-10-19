// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "AmplifierControls.h"
#include "Amplifier.h"

namespace noemixerr
{

AmplifierControls::AmplifierControls(AmplifierEffect* effect) :
	EffectControls(effect),
	m_effect(effect),
	m_volumeModel(100.0f, 0.0f, 200.0f, 0.1f, this, tr("Volume")),
	m_panModel(0.0f, -100.0f, 100.0f, 0.1f, this, tr("Panning")),
	m_leftModel(100.0f, 0.0f, 200.0f, 0.1f, this, tr("Left gain")),
	m_rightModel(100.0f, 0.0f, 200.0f, 0.1f, this, tr("Right gain"))
{
}


void AmplifierControls::loadSettings(const QDomElement& parent)
{
	m_volumeModel.loadSettings(parent, "volume");
	m_panModel.loadSettings(parent, "pan");
	m_leftModel.loadSettings(parent, "left");
	m_rightModel.loadSettings(parent, "right");
}


void AmplifierControls::saveSettings(QDomDocument& doc, QDomElement& parent)
{
	m_volumeModel.saveSettings(doc, parent, "volume"); 
	m_panModel.saveSettings(doc, parent, "pan");
	m_leftModel.saveSettings(doc, parent, "left");
	m_rightModel.saveSettings(doc, parent, "right");
}


} // namespace noemixerr
