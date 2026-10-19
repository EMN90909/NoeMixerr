// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <QLabel>
#include <QPainter>
#include <QIcon>

#include "embed.h"

#include "PeakController.h"

namespace noemixerr::gui
{


PeakControllerDialog::PeakControllerDialog( Controller * _model, QWidget * _parent ) :
	ControllerDialog( _model, _parent )
{
	setWindowTitle( tr( "PEAK" ) );
	setWindowIcon( embed::getIconPixmap( "controller" ) );
	setFixedSize( 256, 64 );
	
	setToolTip(tr("LFO Controller"));

	auto l = new QLabel(this);
	l->setText( "Use FX's controls" );
	l->move(10, 10);

	setModel( _model );
}




/*
void effectView::closeEffects()
{
	m_subWindow->hide();
	m_show = true;
}
*/


void PeakControllerDialog::contextMenuEvent( QContextMenuEvent * )
{
}




void PeakControllerDialog::paintEvent( QPaintEvent * )
{
	QPainter p( this );
}



void PeakControllerDialog::modelChanged()
{
	m_peakController = castModel<PeakController>();
}


} // namespace noemixerr::gui