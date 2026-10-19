// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2007 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.





#include "StereoEnhancerControlDialog.h"
#include <QHBoxLayout>
#include "Knob.h"
#include "StereoEnhancerControls.h"

namespace noemixerr::gui
{


StereoEnhancerControlDialog::StereoEnhancerControlDialog(
	StereoEnhancerControls * _controls ) :
	EffectControlDialog( _controls )
{
	auto l = new QHBoxLayout(this);
	l->setSizeConstraint(QLayout::SetFixedSize);

	auto widthKnob = new Knob(KnobType::Bright26, tr("WIDTH"), this);
	widthKnob->setModel( &_controls->m_widthModel );
	widthKnob->setHintText( tr( "Width:" ) , " samples" );

	l->addWidget( widthKnob );

	this->setLayout(l);
}


} // namespace noemixerr::gui
