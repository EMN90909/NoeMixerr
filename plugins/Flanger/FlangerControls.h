// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef FLANGERCONTROLS_H
#define FLANGERCONTROLS_H

#include "EffectControls.h"
#include "FlangerControlsDialog.h"

namespace noemixerr
{


class FlangerEffect;

class FlangerControls : public EffectControls
{
	Q_OBJECT
public:
	FlangerControls( FlangerEffect* effect );
	~FlangerControls() override = default;
	void saveSettings ( QDomDocument& doc, QDomElement& parent ) override;
	void loadSettings ( const QDomElement &_this ) override;
	inline QString nodeName() const override
	{
		return "Flanger";
	}
	int controlCount() override
	{
		return 7;
	}
	gui::EffectControlDialog* createView() override
	{
		return new gui::FlangerControlsDialog( this );
	}

private slots:
	void changedSampleRate();
	void changedPlaybackState();

private:
	FlangerEffect* m_effect;
	FloatModel m_delayTimeModel;
	TempoSyncKnobModel m_lfoFrequencyModel;
	FloatModel m_lfoAmountModel;
	FloatModel m_lfoPhaseModel;
	FloatModel m_feedbackModel;
	FloatModel m_whiteNoiseAmountModel;
	BoolModel m_invertFeedbackModel;

	friend class gui::FlangerControlsDialog;
	friend class FlangerEffect;

};


} // namespace noemixerr

#endif // FLANGERCONTROLS_H
