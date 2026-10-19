// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _STEREO_MATRIX_CONTROLS_H
#define _STEREO_MATRIX_CONTROLS_H

#include "EffectControls.h"
#include "StereoMatrixControlDialog.h"

namespace noemixerr
{


class StereoMatrixEffect;

class StereoMatrixControls : public EffectControls
{
	Q_OBJECT
public:
	StereoMatrixControls( StereoMatrixEffect( * _eff ) ); 
	~StereoMatrixControls() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return( "stereomatrixcontrols" );
	}

	int controlCount() override
	{
		return( 1 );
	}
	
	gui::EffectControlDialog* createView() override
	{
		return new gui::StereoMatrixControlDialog( this );
	}


private slots:
	void changeMatrix();


private:
	StereoMatrixEffect * m_effect;

	FloatModel m_llModel;
	FloatModel m_lrModel;
	FloatModel m_rlModel;
	FloatModel m_rrModel;
	
	friend class gui::StereoMatrixControlDialog;
	friend class StereoMatrixEffect;

} ;


} // namespace noemixerr

#endif 
