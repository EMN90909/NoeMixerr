// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007-2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QApplication>
#include <QStyle>
#include "NoeMixerrPalette.h"


namespace noemixerr::gui
{

NoeMixerrPalette::NoeMixerrPalette( QWidget * parent, QStyle * stylearg ) : 
	QWidget( parent ),
	
/*	sane defaults in case fetching from stylesheet fails*/	
	
	m_background( 91, 101, 113 ),
	m_windowText( 240, 240, 240 ),
	m_base( 128, 128, 128 ),
	m_text( 224, 224, 224 ),
	m_button( 201, 201, 201 ),
	m_shadow( 0,0,0 ),
	m_buttonText( 0,0,0 ),
	m_brightText( 74, 253, 133 ),
	m_highlight( 100, 100, 100 ),
	m_highlightedText( 255, 255, 255  )
{
	setStyle( stylearg );
	stylearg->polish( this );
	ensurePolished();
}

#define ACCESSMET( read, write ) \
	QColor NoeMixerrPalette:: read () const \
	{	return m_##read ; } \
	void NoeMixerrPalette:: write ( const QColor & c ) \
	{	m_##read = QColor( c ); }
	

	ACCESSMET( background, setBackground )
	ACCESSMET( windowText, setWindowText )
	ACCESSMET( base, setBase )
	ACCESSMET( text, setText )
	ACCESSMET( button, setButton )
	ACCESSMET( shadow, setShadow )
	ACCESSMET( buttonText, setButtonText )
	ACCESSMET( brightText, setBrightText )
	ACCESSMET( highlight, setHighlight )
	ACCESSMET( highlightedText, setHighlightedText )


QPalette NoeMixerrPalette::palette() const
{
	QPalette pal = QApplication::style()->standardPalette();
	
	pal.setColor( QPalette::Window, 			background() );
	pal.setColor( QPalette::WindowText, 		windowText() );	
	pal.setColor( QPalette::Base, 				base() );	
	pal.setColor( QPalette::ButtonText, 		buttonText() );	
	pal.setColor( QPalette::BrightText, 		brightText() );	
	pal.setColor( QPalette::Text, 				text() );	
	pal.setColor( QPalette::Button, 			button() );	
	pal.setColor( QPalette::Shadow, 			shadow() );	
	pal.setColor( QPalette::Highlight, 			highlight() );	
	pal.setColor( QPalette::HighlightedText, 	highlightedText() );
	return pal;
}


} // namespace noemixerr::gui
