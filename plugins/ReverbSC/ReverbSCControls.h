// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017 Paul Batchelor
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef REVERBSC_CONTROLS_H
#define REVERBSC_CONTROLS_H

#include "EffectControls.h"
#include "ReverbSCControlDialog.h"


namespace noemixerr
{


class ReverbSCEffect;

class ReverbSCControls : public EffectControls
{
	Q_OBJECT
public:
	ReverbSCControls( ReverbSCEffect* effect );
	~ReverbSCControls() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "ReverbSCControls";
	}

	int controlCount() override
	{
		return 4;
	}

	gui::EffectControlDialog* createView() override
	{
		return new gui::ReverbSCControlDialog( this );
	}


private slots:
	void changeControl();
	void changeSampleRate();

private:
	ReverbSCEffect* m_effect;
	FloatModel m_inputGainModel;
	FloatModel m_sizeModel;
	FloatModel m_colorModel;
	FloatModel m_outputGainModel;

	friend class gui::ReverbSCControlDialog;
	friend class ReverbSCEffect;

} ;


} // namespace noemixerr

#endif
