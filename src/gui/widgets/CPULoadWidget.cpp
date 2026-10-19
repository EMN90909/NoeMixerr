// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <algorithm>
#include <QPainter>

#include "AudioEngine.h"
#include "CPULoadWidget.h"
#include "embed.h"
#include "Engine.h"


namespace noemixerr::gui
{


CPULoadWidget::CPULoadWidget( QWidget * _parent ) :
	QWidget( _parent ),
	m_currentLoad( 0 ),
	m_temp(),
	m_background( embed::getIconPixmap( "cpuload_bg" ) ),
	m_leds( embed::getIconPixmap( "cpuload_leds" ) ),
	m_changed( true ),
	m_updateTimer()
{
	setFixedSize( m_background.width(), m_background.height() );

	m_temp = QPixmap( width(), height() );
	

	connect( &m_updateTimer, SIGNAL(timeout()),
					this, SLOT(updateCpuLoad()));
	m_updateTimer.start( 100 );	// update cpu-load at 10 fps
}







void CPULoadWidget::paintEvent( QPaintEvent *  )
{
	if( m_changed == true )
	{
		m_changed = false;
		
		m_temp.fill( QColor(0,0,0,0) );
		QPainter p( &m_temp );
		p.drawPixmap( 0, 0, m_background );

		// Normally the CPU load indicator moves smoothly, with 1 pixel resolution. However, some themes may want to
		// draw discrete elements (like LEDs), so the stepSize property can be used to specify a larger step size.
		int w = (m_leds.width() * std::min(m_currentLoad, 100) / (stepSize() * 100)) * stepSize();
		if( w > 0 )
		{
			p.drawPixmap( 23, 3, m_leds, 0, 0, w,
							m_leds.height() );
		}
	}
	QPainter p( this );
	p.drawPixmap( 0, 0, m_temp );
}




void CPULoadWidget::updateCpuLoad()
{
	// Additional display smoothing for the main load-value. Stronger averaging
	// cannot be used directly in the profiler: cpuLoad() must react fast enough
	// to be useful as overload indicator in AudioEngine::criticalXRuns().
	const int new_load = (m_currentLoad + Engine::audioEngine()->cpuLoad()) / 2;

	if (new_load != m_currentLoad)
	{
		auto engine = Engine::audioEngine();
		setToolTip(
			tr("DSP total: %1%").arg(new_load) + "\n"
			+ tr(" - Notes and setup: %1%").arg(engine->detailLoad(AudioEngineProfiler::DetailType::NoteSetup)) + "\n"
			+ tr(" - Instruments: %1%").arg(engine->detailLoad(AudioEngineProfiler::DetailType::Instruments)) + "\n"
			+ tr(" - Effects: %1%").arg(engine->detailLoad(AudioEngineProfiler::DetailType::Effects)) + "\n"
			+ tr(" - Mixing: %1%").arg(engine->detailLoad(AudioEngineProfiler::DetailType::Mixing))
		);
		m_currentLoad = new_load;
		m_changed = true;
		update();
	}
}


} // namespace noemixerr::gui
