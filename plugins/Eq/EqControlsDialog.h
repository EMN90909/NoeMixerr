// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef EQCONTROLSDIALOG_H
#define EQCONTROLSDIALOG_H


#include "EffectControlDialog.h"

namespace noemixerr
{

class BoolModel;
class FloatModel;

class EqControls;

namespace gui
{

class EqBand;
class EqParameterWidget;

class EqControlsDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	EqControlsDialog( EqControls * controls );
	~EqControlsDialog() override = default;

	EqBand * setBand( EqControls * controls );

private:
	EqControls * m_controls;
	EqParameterWidget * m_parameterWidget;

	void mouseDoubleClickEvent(QMouseEvent *event) override;

	EqBand *setBand( int index, BoolModel *active, FloatModel *freq, FloatModel *res, FloatModel *gain, QColor color, QString name, float *peakL, float *peakR, BoolModel *hp12, BoolModel *hp24, BoolModel *hp48, BoolModel *lp12, BoolModel *lp24, BoolModel *lp48 );

	int m_originalHeight;
};


} // namespace gui

} // namespace noemixerr

#endif // EQCONTROLSDIALOG_H
