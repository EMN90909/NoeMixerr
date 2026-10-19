// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/yahoo.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "MeterDialog.h"
#include "MeterModel.h"
#include "LcdSpinBox.h"

namespace noemixerr::gui
{


MeterDialog::MeterDialog( QWidget * _parent, bool _simple ) :
	QWidget( _parent ),
	ModelView( nullptr, this )
{
	auto vlayout = new QVBoxLayout(this);
	vlayout->setSpacing( 0 );
	vlayout->setContentsMargins(0, 0, 0, 0);

	auto num = new QWidget(this);
	auto num_layout = new QHBoxLayout(num);
	num_layout->setSpacing( 0 );
	num_layout->setContentsMargins(0, 0, 0, 0);


	m_numerator = new LcdSpinBox( 2, num, tr( "Meter Numerator" ) );
	m_numerator->setToolTip(tr("Meter numerator"));

	num_layout->addWidget( m_numerator );

	if( !_simple )
	{
		auto num_label = new QLabel(tr("Meter Numerator"), num);
		QFont f = num_label->font();
		num_layout->addSpacing( 5 );
		num_layout->addWidget( num_label );
	}
	num_layout->addStretch();

	auto den = new QWidget(this);
	auto den_layout = new QHBoxLayout(den);
	den_layout->setSpacing( 0 );
	den_layout->setContentsMargins(0, 0, 0, 0);

	m_denominator = new LcdSpinBox( 2, den, tr( "Meter Denominator" ) );
	m_denominator->setToolTip(tr("Meter denominator"));
	if( _simple )
	{
		m_denominator->setLabel( tr( "TIME SIG" ) );
	}

	den_layout->addWidget( m_denominator );

	if( !_simple )
	{
		auto den_label = new QLabel(tr("Meter Denominator"), den);
		QFont f = den_label->font();
		den_layout->addSpacing( 5 );
		den_layout->addWidget( den_label );
	}
	den_layout->addStretch();


	vlayout->addSpacing( _simple ? 1 : 3 );
	vlayout->addWidget( num );
	vlayout->addSpacing( 2 );
	vlayout->addWidget( den );
	vlayout->addStretch();
}







void MeterDialog::modelChanged()
{
	auto mm = castModel<MeterModel>();
	m_numerator->setModel( &mm->numeratorModel() );
	m_denominator->setModel( &mm->denominatorModel() );
}


} // namespace noemixerr::gui
