// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LED_CHECKBOX_H
#define NoeMixerr_GUI_LED_CHECKBOX_H

#include "AutomatableButton.h"




namespace noemixerr::gui
{

class NoeMixerr_EXPORT LedCheckBox : public AutomatableButton
{
	Q_OBJECT
public:
	enum class LedColor
	{
		Yellow,
		Green,
		Red
	} ;

	LedCheckBox( const QString & _txt, QWidget * _parent,
				const QString & _name = QString(),
						LedColor _color = LedColor::Yellow,
						bool legacyMode = true);
	LedCheckBox( QWidget * _parent,
				const QString & _name = QString(),
						LedColor _color = LedColor::Yellow,
						bool legacyMode = true);

	inline const QString & text()
	{
		return( m_text );
	}

	void setText( const QString& s );
	void setLedColor(LedColor color);

	Q_PROPERTY( QString text READ text WRITE setText )

protected:
	void paintEvent( QPaintEvent * _pe ) override;


private:
	QPixmap m_ledOnPixmap;
	QPixmap m_ledOffPixmap;

	QString m_text;

	bool m_legacyMode;
	

	void onTextUpdated(); //!< to be called when you updated @a m_text
	void paintLegacy(QPaintEvent * p);
	void paintNonLegacy(QPaintEvent * p);

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_LED_CHECKBOX_H
