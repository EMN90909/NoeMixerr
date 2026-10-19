// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LCD_WIDGET_H
#define NoeMixerr_GUI_LCD_WIDGET_H

#include <QMap>
#include <QWidget>

#include "noemixerr_export.h"

namespace noemixerr::gui
{

class NoeMixerr_EXPORT LcdWidget : public QWidget
{
	Q_OBJECT
	
	// theming qproperties
	Q_PROPERTY( QColor textColor READ textColor WRITE setTextColor )
	Q_PROPERTY( QColor textShadowColor READ textShadowColor WRITE setTextShadowColor )
	
public:
	explicit LcdWidget(QWidget* parent, const QString& name = QString(), bool leadingZero = false);
	LcdWidget(int numDigits, QWidget* parent, const QString& name = QString(), bool leadingZero = false);
	LcdWidget(int numDigits, const QString& style, QWidget* parent, const QString& name = QString(),
		bool leadingZero = false);

	void setValue(int value);
	void setValue(float value);
	void setLabel(const QString& label);

	void addTextForValue( int value, const QString& text )
	{
		m_textForValue[value] = text;
		update();
	}

	Q_PROPERTY( int numDigits READ numDigits WRITE setNumDigits )

	inline int numDigits() const { return m_numDigits; }
	inline void setNumDigits( int n ) { m_numDigits = n; updateSize(); }
	
	QColor textColor() const;
	void setTextColor( const QColor & c );
	
	QColor textShadowColor() const;
	void setTextShadowColor( const QColor & c );

	int cellHeight() const { return m_cellHeight; }

	void setSeamless(bool left, bool right)
	{
		m_seamlessLeft = left;
		m_seamlessRight = right;
		updateSize();
	}

public slots:
	virtual void setMarginWidth( int width );


protected:
	void paintEvent( QPaintEvent * pe ) override;

	virtual void updateSize();


private:

	static const int charsPerPixmap = 12;

	QMap<int, QString> m_textForValue;

	QString m_display;

	QString m_label;
	QPixmap m_lcdPixmap;

	QColor m_textColor;
	QColor m_textShadowColor;

	int m_cellWidth;
	int m_cellHeight;
	int m_numDigits;
	int m_marginWidth;
	bool m_seamlessLeft;
	bool m_seamlessRight;
	bool m_leadingZero;

	void initUi( const QString& name, const QString &style ); //!< to be called by ctors

};

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_LCD_WIDGET_H
