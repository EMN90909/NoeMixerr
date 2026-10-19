// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.

 
#ifndef MULTITAP_ECHO_CONTROLS_H
#define MULTITAP_ECHO_CONTROLS_H

#include "EffectControls.h"
#include "MultitapEchoControlDialog.h"
#include "Graph.h"

namespace noemixerr
{


class MultitapEchoEffect;

class MultitapEchoControls : public EffectControls
{
	Q_OBJECT
public:
	MultitapEchoControls( MultitapEchoEffect * eff );
	~MultitapEchoControls() override = default;

	void saveSettings( QDomDocument & doc, QDomElement & parent ) override;
	void loadSettings( const QDomElement & elem ) override;
	inline QString nodeName() const override
	{
		return( "multitapechocontrols" );
	}

	void setDefaultAmpShape();
	void setDefaultLpShape();

	int controlCount() override
	{
		return( 5 );
	}

	gui::EffectControlDialog* createView() override
	{
		return( new gui::MultitapEchoControlDialog( this ) );
	}

private slots:
	void ampSamplesChanged( int, int );
	void ampResetClicked();
	
	void lpSamplesChanged( int, int );
	void lpResetClicked();
	
	void lengthChanged();
	void sampleRateChanged();

private:
	MultitapEchoEffect * m_effect;
	IntModel m_steps;
	TempoSyncKnobModel m_stepLength;
	
	FloatModel m_dryGain;
	BoolModel m_swapInputs;
	FloatModel m_stages;
	
	graphModel m_ampGraph;
	graphModel m_lpGraph;

	friend class MultitapEchoEffect;
	friend class gui::MultitapEchoControlDialog;
};


} // namespace noemixerr

#endif
