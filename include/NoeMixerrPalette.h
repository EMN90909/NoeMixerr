// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007-2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_NoeMixerr_PALETTE_H
#define NoeMixerr_GUI_NoeMixerr_PALETTE_H

#include <QWidget>
#include "noemixerr_export.h"

namespace noemixerr::gui
{


class NoeMixerr_EXPORT NoeMixerrPalette : public QWidget
{
	Q_OBJECT
	Q_PROPERTY( QColor background READ background WRITE setBackground )
	Q_PROPERTY( QColor windowText READ windowText WRITE setWindowText )
	Q_PROPERTY( QColor base READ base WRITE setBase )
	Q_PROPERTY( QColor text READ text WRITE setText )
	Q_PROPERTY( QColor button READ button WRITE setButton )
	Q_PROPERTY( QColor shadow READ shadow WRITE setShadow )
	Q_PROPERTY( QColor buttonText READ buttonText WRITE setButtonText )
	Q_PROPERTY( QColor brightText READ brightText WRITE setBrightText )
	Q_PROPERTY( QColor highlight READ highlight WRITE setHighlight )
	Q_PROPERTY( QColor highlightedText READ highlightedText WRITE setHighlightedText )

public:
	NoeMixerrPalette( QWidget * parent, QStyle * stylearg  ); 
	~NoeMixerrPalette() override = default;

#define ACCESSMET( read, write ) \
	QColor read () const; \
	void write ( const QColor & c ); \


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

#undef ACCESSMET

	QPalette palette() const;

private:
	QColor m_background;
	QColor m_windowText;
	QColor m_base;
	QColor m_text;
	QColor m_button;
	QColor m_shadow;
	QColor m_buttonText;
	QColor m_brightText;
	QColor m_highlight;
	QColor m_highlightedText;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_NoeMixerr_PALETTE_H
