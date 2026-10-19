// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2015 Steffen Baranowsky <BaraMGB/at/freenet/dot/de>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef EQCURVE_H
#define EQCURVE_H

#include <QGraphicsObject>


namespace noemixerr::gui
{


enum class EqHandleType {
	HighPass=1,
	LowShelf,
	Para,
	HighShelf,
	LowPass
};




// implements the Eq_Handle to control a band
class EqHandle : public QGraphicsObject
{
	Q_OBJECT
public:
	EqHandle( int num, int x, int y );

	static float freqToXPixel( float freq, int w );
	static float xPixelToFreq( float x , int w );
	static float gainToYPixel( float gain, int h, float pixelPerUnitHeight );
	static float yPixelToGain( float y, int h, float pixelPerUnitHeight );

	QRectF boundingRect() const override;
	QPainterPath getCurvePath();
	float getPeakCurve( float x );
	float getHighShelfCurve( float x );
	float getLowShelfCurve( float x );
	float getLowCutCurve( float x );
	float getHighCutCurve( float x );
	float getResonance();
	int getNum();
	EqHandleType getType();
	void setType( EqHandleType t );
	void setResonance( float r );
	bool isMouseHover();
	void setMouseHover( bool d );
	bool isActiveHandle();
	void setHandleActive( bool a );
	bool mousePressed() const;
	void sethp12();
	void sethp24();
	void sethp48();
	void setlp12();
	void setlp24();
	void setlp48();

signals:
	void positionChanged();

protected:
	void mousePressEvent( QGraphicsSceneMouseEvent *event ) override;
	void mouseReleaseEvent( QGraphicsSceneMouseEvent *event ) override;
	void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) override;
	void wheelEvent( QGraphicsSceneWheelEvent *wevent ) override;
	void hoverEnterEvent( QGraphicsSceneHoverEvent *hevent ) override;
	void hoverLeaveEvent( QGraphicsSceneHoverEvent *hevent ) override;
	QVariant itemChange( GraphicsItemChange change, const QVariant &value ) override;

private:
	double calculateGain( const double freq, const double a1, const double a2, const double b0, const double b1, const double b2 );
	void loadPixmap();
	float m_pixelsPerUnitWidth;
	float m_pixelsPerUnitHeight;
	float m_scale;
	bool m_hp12;
	bool m_hp24;
	bool m_hp48;
	bool m_lp12;
	bool m_lp24;
	bool m_lp48;
	bool m_mouseHover;
	EqHandleType m_type;
	int m_numb;
	float m_width, m_heigth;
	float m_resonance;
	bool m_mousePressed;
	bool m_active;
	QPixmap m_circlePixmap;
};




class EqCurve : public QGraphicsObject
{
	Q_OBJECT
public:
	EqCurve( QList<EqHandle*> *handle, int x, int y );
	QRectF boundingRect() const override;
	void setModelChanged(bool mc);

protected:
	void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) override;

private:
	QList<EqHandle*> *m_handle;
	QPainterPath m_curve;
	QPixmap m_curvePixmapCache;
	int m_width, m_heigth;
	int m_alpha;
	bool m_modelChanged;
	float m_pixelsPerUnitHeight;
	float m_scale;
};


} // namespace noemixerr::gui

#endif // EQCURVE_H
