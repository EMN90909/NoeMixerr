// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024- Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef NoeMixerr_GUI_PEAKINDICATOR_H
#define NoeMixerr_GUI_PEAKINDICATOR_H

#include "noemixerr_export.h"

#include <QLabel>


namespace noemixerr::gui
{

class NOEMIXERR_EXPORT PeakIndicator : public QLabel
{
	Q_OBJECT
public:
	PeakIndicator(QWidget* parent);

	void resetPeakToMinusInf();

public slots:
	void updatePeak(float peak);

protected:
	void mousePressEvent(QMouseEvent* e) override;

private:
	void updatePeakDisplay();

private:
	float m_peak;
} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_PEAKINDICATOR_H
