// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _STEREO_ENHANCER_CONTROLS_H
#define _STEREO_ENHANCER_CONTROLS_H

#include "EffectControls.h"
#include "StereoEnhancerControlDialog.h"

namespace noemixerr
{


class StereoEnhancerEffect;

class StereoEnhancerControls : public EffectControls
{
	Q_OBJECT
public:
	StereoEnhancerControls( StereoEnhancerEffect( * _eff ) ); 
	~StereoEnhancerControls() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return( "stereoenhancercontrols" );
	}

	int controlCount() override
	{
		return( 1 );
	}
	
	gui::EffectControlDialog* createView() override
	{
		return new gui::StereoEnhancerControlDialog( this );
	}


private slots:
	void changeWideCoeff();


private:
	StereoEnhancerEffect * m_effect;
	FloatModel m_widthModel;
	
	friend class gui::StereoEnhancerControlDialog;

} ;


} // namespace noemixerr

#endif /*_STEREO_ENHANCER_CONTROLS_H*/
