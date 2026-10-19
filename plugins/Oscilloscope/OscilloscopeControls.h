// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025-2026 Keratin
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_OSCILLOSCOPE_CONTROLS_H
#define NoeMixerr_OSCILLOSCOPE_CONTROLS_H

#include "EffectControls.h"

namespace noemixerr
{

class Oscilloscope;

namespace gui
{
class OscilloscopeControlDialog;
class OscilloscopeGraph;
}

class OscilloscopeControls : public EffectControls
{
	Q_OBJECT
public:
	OscilloscopeControls(Oscilloscope* effect);
	~OscilloscopeControls() override = default;

	void saveSettings(QDomDocument& doc, QDomElement& parent) override;
	void loadSettings(const QDomElement& parent) override;
	QString nodeName() const override { return "OscilloscopeControls"; }
	gui::EffectControlDialog* createView() override;
	int controlCount() override { return 5; }

private:
	FloatModel m_ampModel;
	FloatModel m_lengthModel;
	FloatModel m_phaseModel;
	BoolModel m_pauseModel;
	BoolModel m_stereoModel;

	Oscilloscope* m_effect;

	friend class gui::OscilloscopeControlDialog;
	friend class gui::OscilloscopeGraph;
	friend class Oscilloscope;
};

} // namespace noemixerr

#endif // NoeMixerr_OSCILLOSCOPE_CONTROLS_H
