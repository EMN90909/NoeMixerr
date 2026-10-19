// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef EQFADER_H
#define EQFADER_H
#include <QList>
#include <QWidget>

#include "EffectControls.h"
#include "Fader.h"
#include "GuiApplication.h"
#include "MainWindow.h"
#include "TextFloat.h"

namespace noemixerr::gui
{


class EqFader : public Fader
{

public:
	Q_OBJECT
public:
	EqFader( FloatModel * model, const QString & name, QWidget * parent,  float* lPeak, float* rPeak ) :
		Fader(model, name, parent, false)
	{
		setMinimumSize( 23, 116 );
		setMaximumSize( 23, 116 );
		resize( 23, 116 );
		m_lPeak = lPeak;
		m_rPeak = rPeak;
		connect( getGUI()->mainWindow(), SIGNAL( periodicUpdate() ), this, SLOT( updateVuMeters() ) );
		m_model = model;
		setPeak_L( 0 );
		setPeak_R( 0 );
	}



	~EqFader() override = default;


private slots:

	void updateVuMeters()
	{
		const float opl = getPeak_L();
		const float opr = getPeak_R();
		const float fallOff = 1.07f;
		if( *m_lPeak > opl )
		{
			setPeak_L( *m_lPeak );
			*m_lPeak = 0;
		}
		else
		{
			setPeak_L( opl/fallOff );
		}

		if( *m_rPeak > opr )
		{
			setPeak_R( *m_rPeak );
			*m_rPeak = 0;
		}
		else
		{
			setPeak_R( opr/fallOff );
		}
		update();
	}




private:
	float* m_lPeak;
	float* m_rPeak;
	FloatModel* m_model;

};


} // namespace noemixerr::gui

#endif // EQFADER_H
