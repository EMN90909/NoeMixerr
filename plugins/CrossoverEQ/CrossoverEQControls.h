// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef CROSSOVEREQ_CONTROLS_H
#define CROSSOVEREQ_CONTROLS_H

#include "EffectControls.h"
#include "CrossoverEQControlDialog.h"

namespace noemixerr
{

class CrossoverEQEffect;

class CrossoverEQControls : public EffectControls
{
	Q_OBJECT
public:
	CrossoverEQControls( CrossoverEQEffect * eff );
	~CrossoverEQControls() override = default;

	void saveSettings( QDomDocument & doc, QDomElement & elem ) override;
	void loadSettings( const QDomElement & elem ) override;
	inline QString nodeName() const override
	{
		return( "crossoevereqcontrols" );
	}

	int controlCount() override
	{
		return( 11 );
	}

	gui::EffectControlDialog * createView() override
	{
		return( new gui::CrossoverEQControlDialog( this ) );
	}

private slots:
	void xover12Changed();
	void xover23Changed();
	void xover34Changed();
	void sampleRateChanged();

private:
	CrossoverEQEffect * m_effect;
	
	FloatModel m_xover12;
	FloatModel m_xover23;
	FloatModel m_xover34;
	
	FloatModel m_gain1;
	FloatModel m_gain2;
	FloatModel m_gain3;
	FloatModel m_gain4;
	
	BoolModel m_mute1;
	BoolModel m_mute2;
	BoolModel m_mute3;
	BoolModel m_mute4;
	
	friend class gui::CrossoverEQControlDialog;
	friend class CrossoverEQEffect;
};


} // namespace noemixerr

#endif
