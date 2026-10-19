// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef DELAYCONTROLS_H
#define DELAYCONTROLS_H

#include "EffectControls.h"
#include "DelayControlsDialog.h"

namespace noemixerr
{


class DelayEffect;


class DelayControls : public EffectControls
{
	Q_OBJECT
public:
	DelayControls( DelayEffect* effect );
	~DelayControls() override = default;
	void saveSettings( QDomDocument& doc, QDomElement& parent ) override;
	void loadSettings( const QDomElement& _this ) override;
	inline QString nodeName() const override
	{
		return "Delay";
	}
	int controlCount() override{
		return 5;
	}
	gui::EffectControlDialog* createView() override
	{
		return new gui::DelayControlsDialog( this );
	}

	float m_outPeakL;
	float m_outPeakR;


private slots:
	void changeSampleRate();

private:
	DelayEffect* m_effect;
	TempoSyncKnobModel m_delayTimeModel;
	FloatModel m_feedbackModel;
	TempoSyncKnobModel m_lfoTimeModel;
	TempoSyncKnobModel m_lfoAmountModel;
	FloatModel m_outGainModel;

	friend class gui::DelayControlsDialog;
	friend class DelayEffect;
};


} // namespace noemixerr

#endif // DELAYCONTROLS_H
