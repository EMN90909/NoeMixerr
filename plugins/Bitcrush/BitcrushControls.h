// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef BITCRUSH_CONTROLS_H
#define BITCRUSH_CONTROLS_H

#include "EffectControls.h"
#include "BitcrushControlDialog.h"

namespace noemixerr
{


class BitcrushEffect;

class BitcrushControls : public EffectControls
{
	Q_OBJECT
public:
	BitcrushControls( BitcrushEffect * eff );
	~BitcrushControls() override = default;

	void saveSettings( QDomDocument & doc, QDomElement & elem ) override;
	void loadSettings( const QDomElement & elem ) override;
	inline QString nodeName() const override
	{
		return( "bitcrushcontrols" );
	}

	int controlCount() override
	{
		return( 9 );
	}

	gui::EffectControlDialog * createView() override
	{
		return( new gui::BitcrushControlDialog( this ) );
	}

private slots:
	void sampleRateChanged();

private:
	BitcrushEffect * m_effect;
	
	FloatModel m_inGain;
	FloatModel m_inNoise;
	
	FloatModel m_outGain;
	FloatModel m_outClip;
	
	FloatModel m_rate;
	FloatModel m_stereoDiff;
	
	FloatModel m_levels;
	
	BoolModel m_rateEnabled;
	BoolModel m_depthEnabled;
	
	friend class gui::BitcrushControlDialog;
	friend class BitcrushEffect;
};


} // namespace noemixerr

#endif
