// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef WAVESHAPER_CONTROLS_H
#define WAVESHAPER_CONTROLS_H

#include "EffectControls.h"
#include "WaveShaperControlDialog.h"
#include "Graph.h"

namespace noemixerr
{


class WaveShaperEffect;


class WaveShaperControls : public EffectControls
{
	Q_OBJECT
public:
	WaveShaperControls( WaveShaperEffect * _eff );
	~WaveShaperControls() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return( "waveshapercontrols" );
	}

	virtual void setDefaultShape();

	int controlCount() override
	{
		return( 4 );
	}

	gui::EffectControlDialog* createView() override
	{
		return( new gui::WaveShaperControlDialog( this ) );
	}


private slots:
	void samplesChanged( int, int );

	void resetClicked();
	void smoothClicked();

	void addOneClicked();
	void subOneClicked();

private:
	WaveShaperEffect * m_effect;
	FloatModel m_inputModel;
	FloatModel m_outputModel;
	graphModel m_wavegraphModel;
	BoolModel  m_clipModel;

	friend class gui::WaveShaperControlDialog;
	friend class WaveShaperEffect;

} ;


} // namespace noemixerr

#endif
