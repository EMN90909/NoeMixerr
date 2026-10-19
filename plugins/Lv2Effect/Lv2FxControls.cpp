// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Lv2FxControls.h"


#include "Engine.h"
#include "Lv2Effect.h"
#include "Lv2FxControlDialog.h"

namespace noemixerr
{


Lv2FxControls::Lv2FxControls(class Lv2Effect *effect, const QString& uri) :
	EffectControls(effect),
	Lv2ControlBase(this, uri)
{
	connect(Engine::audioEngine(), &AudioEngine::sampleRateChanged,
		this, &Lv2FxControls::onSampleRateChanged);
}




void Lv2FxControls::reload()
{
	Lv2ControlBase::reload();
	emit modelChanged();
}




void Lv2FxControls::onSampleRateChanged()
{
	// TODO: once lv2 options are implemented,
	//       plugins that support it might allow changing their samplerate
	//       through it instead of reloading
	reload();
}




void Lv2FxControls::saveSettings(QDomDocument &doc, QDomElement &that)
{
	Lv2ControlBase::saveSettings(doc, that);
}




void Lv2FxControls::loadSettings(const QDomElement &that)
{
	Lv2ControlBase::loadSettings(that);
}




int Lv2FxControls::controlCount()
{
	return static_cast<int>(Lv2ControlBase::controlCount());
}




gui::EffectControlDialog *Lv2FxControls::createView()
{
	return new gui::Lv2FxControlDialog(this);
}




void Lv2FxControls::changeControl() // TODO: what is that?
{
	//	engine::getSong()->setModified();
}


} // namespace noemixerr
