// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
// Copyright (c) 2015 Steffen Baranowsky <BaraMGB/at/freenet/dot/de>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef EQPARAMETERWIDGET_H
#define EQPARAMETERWIDGET_H

#include <QWidget>


namespace noemixerr
{

class BoolModel;
class EqControls;
class FloatModel;


namespace gui
{

class EqCurve;
class EqHandle;

class EqBand
{
public :
	EqBand();
	FloatModel *gain;
	FloatModel *res;
	FloatModel *freq;
	BoolModel *active;
	BoolModel *hp12;
	BoolModel *hp24;
	BoolModel *hp48;
	BoolModel *lp12;
	BoolModel *lp24;
	BoolModel *lp48;
	QColor color;
	int x;
	int y;
	QString name;
	float *peakL;
	float *peakR;
};




class EqParameterWidget : public QWidget
{
	Q_OBJECT
public:
	explicit EqParameterWidget( QWidget *parent = 0, EqControls * controls = 0 );
	~EqParameterWidget() override;
	QList<EqHandle*> m_handleList;

	const int bandCount()
	{
		return 8;
	}

	EqBand* getBandModels( int i );
	void changeHandle( int i );

private:
	float m_pixelsPerUnitWidth;
	float m_pixelsPerUnitHeight;
	float m_pixelsPerOctave;
	float m_scale;
	int m_displayWidth, m_displayHeigth;
	EqControls *m_controls;
	EqBand *m_bands;
	EqHandle *m_handle;
	EqCurve *m_eqcurve;


private slots:
	void updateModels();
	void updateHandle();
};


} // namespace gui

} // namespace noemixerr

#endif // EQPARAMETERWIDGET_H
