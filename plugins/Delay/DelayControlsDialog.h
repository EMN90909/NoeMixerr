// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef DELAYCONTROLSDIALOG_H
#define DELAYCONTROLSDIALOG_H

#include "EffectControlDialog.h"

namespace noemixerr
{


class DelayControls;
class FloatModel;

namespace gui
{

class DelayControlsDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	DelayControlsDialog( DelayControls* controls );
	~DelayControlsDialog() override = default;
};

class XyPad : public QWidget
{
	Q_OBJECT
public:
	XyPad( QWidget *parent = 0, FloatModel *xModel = 0, FloatModel *yModel = 0 );
	~XyPad() override = default;

protected:
	void paintEvent ( QPaintEvent * event ) override;
	void mousePressEvent(QMouseEvent * event ) override;
	void mouseReleaseEvent(QMouseEvent * event) override;
	void mouseMoveEvent(QMouseEvent * event) override;

private:
	FloatModel *m_xModel;
	FloatModel *m_yModel;
	bool m_acceptInput;
};


} // namespace gui

} // namespace noemixerr

#endif // DELAYCONTROLSDIALOG_H
