// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024- Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "PeakIndicator.h"

#include "noemixerr_math.h"

#include <QMouseEvent>


namespace noemixerr::gui
{

PeakIndicator::PeakIndicator(QWidget* parent) :
	QLabel(parent),
	m_peak(0.f)
{
	setAlignment(Qt::AlignCenter);

	updatePeakDisplay();
}

void PeakIndicator::resetPeakToMinusInf()
{
	m_peak = 0;
	updatePeakDisplay();
}

void PeakIndicator::updatePeak(float peak)
{
	if (peak > m_peak)
	{
		m_peak = peak;
		updatePeakDisplay();
	}
}

void PeakIndicator::mousePressEvent(QMouseEvent* e)
{
	if (e->buttons() & Qt::LeftButton)
	{
		resetPeakToMinusInf();
	}
}

void PeakIndicator::updatePeakDisplay()
{
	// Treat everything below -144 dbFS as -inf. Otherwise some residual signals show up
	// in the form of very small dbFS values, e.g. -857.1 dbFS.
	// TODO Make the threshold configurable in the settings?
	if (m_peak <= dbfsToAmp(-144.))
	{
		setText(tr("-inf"));
	}
	else
	{
		auto dbfs = ampToDbfs(m_peak);
		setText(QString::number(dbfs, 'f', 1));
	}
}

} // namespace noemixerr::gui
