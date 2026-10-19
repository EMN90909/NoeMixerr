// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _PEAK_CONTROLLER_EFFECT_CONTROLS_H
#define _PEAK_CONTROLLER_EFFECT_CONTROLS_H

#include "EffectControls.h"
#include "PeakControllerEffectControlDialog.h"

namespace noemixerr
{


class PeakControllerEffect;


class PeakControllerEffectControls : public EffectControls
{
	Q_OBJECT
public:
	PeakControllerEffectControls( PeakControllerEffect * _eff );
	~PeakControllerEffectControls() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "peakcontrollereffectcontrols";
	}

	int controlCount() override
	{
		return 1;
	}
	gui::EffectControlDialog * createView() override
	{
		return new gui::PeakControllerEffectControlDialog( this );
	}


private:
	PeakControllerEffect * m_effect;

	FloatModel m_baseModel;
	FloatModel m_amountModel;
	FloatModel m_attackModel;
	FloatModel m_decayModel;
	FloatModel m_tresholdModel;
	BoolModel m_muteModel;
	BoolModel m_absModel;
	FloatModel m_amountMultModel;

	friend class gui::PeakControllerEffectControlDialog;
	friend class PeakControllerEffect;

} ;


} // namespace noemixerr

#endif
