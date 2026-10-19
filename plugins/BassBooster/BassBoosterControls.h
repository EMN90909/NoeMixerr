// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef BASSBOOSTER_CONTROLS_H
#define BASSBOOSTER_CONTROLS_H

#include "EffectControls.h"
#include "BassBoosterControlDialog.h"

namespace noemixerr
{

class BassBoosterEffect;


class BassBoosterControls : public EffectControls
{
	Q_OBJECT
public:
	BassBoosterControls( BassBoosterEffect* effect );
	~BassBoosterControls() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "bassboostercontrols";
	}

	int controlCount() override
	{
		return 3;
	}

	gui::EffectControlDialog* createView() override
	{
		return new gui::BassBoosterControlDialog( this );
	}


private slots:
	void changeFrequency();

private:
	BassBoosterEffect* m_effect;
	FloatModel m_freqModel;
	FloatModel m_gainModel;
	FloatModel m_ratioModel;

	friend class gui::BassBoosterControlDialog;
	friend class BassBoosterEffect;
} ;


} // namespace noemixerr

#endif
