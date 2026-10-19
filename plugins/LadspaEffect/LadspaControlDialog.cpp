// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <cmath>

#include <QHBoxLayout>
#include <QGroupBox>
#include <QVBoxLayout>

#include "LadspaBase.h"
#include "LadspaControl.h"
#include "LadspaControls.h"
#include "LadspaControlDialog.h"
#include "LadspaControlView.h"
#include "LedCheckBox.h"

namespace noemixerr::gui
{


LadspaControlDialog::LadspaControlDialog( LadspaControls * _ctl ) :
	EffectControlDialog( _ctl ),
	m_effectLayout( nullptr ),
	m_stereoLink( nullptr )
{
	auto mainLay = new QVBoxLayout(this);

	m_effectLayout = new QHBoxLayout();
	mainLay->addLayout( m_effectLayout );

	updateEffectView( _ctl );

	if( _ctl->m_processors > 1 )
	{
		mainLay->addSpacing( 3 );
		auto center = new QHBoxLayout();
		mainLay->addLayout( center );
		m_stereoLink = new LedCheckBox( tr( "Link Channels" ), this );
		m_stereoLink->setModel( &_ctl->m_stereoLinkModel );
		center->addWidget( m_stereoLink );
	}
}




void LadspaControlDialog::updateEffectView( LadspaControls * _ctl )
{
	QList<QGroupBox *> groupBoxes = findChildren<QGroupBox *>();
	for (const auto& groupBox : groupBoxes)
	{
		delete groupBox;
	}

	m_effectControls = _ctl;


	const int cols = static_cast<int>( sqrt( 
		static_cast<double>( _ctl->m_controlCount /
						_ctl->m_processors ) ) );
	for( ch_cnt_t proc = 0; proc < _ctl->m_processors; proc++ )
	{
		control_list_t & controls = _ctl->m_controls[proc];
		int row = 0;
		int col = 0;
		BufferDataType last_port = BufferDataType::None;

		auto grouper = _ctl->m_processors > 1
			? new QGroupBox(tr("Channel ") + QString::number(proc + 1), this)
			: new QGroupBox(this);

		auto gl = new QGridLayout(grouper);
		grouper->setLayout( gl );
		grouper->setAlignment( Qt::Vertical );

		for (const auto& control : controls)
		{
			if (control->port()->proc == proc)
			{
				BufferDataType this_port = control->port()->data_type;
				if( last_port != BufferDataType::None &&
					( this_port == BufferDataType::Toggled || this_port == BufferDataType::Enum ) &&
					( last_port != BufferDataType::Toggled && last_port != BufferDataType::Enum ) )
				{
					++row;
					col = 0;
				}
				gl->addWidget(new LadspaControlView(grouper, control), row, col);
				if( ++col == cols )
				{
					++row;
					col = 0;
				}
				last_port = control->port()->data_type;
			}
		}

		m_effectLayout->addWidget( grouper );
	}

	if( _ctl->m_processors > 1 && m_stereoLink != nullptr )
	{
		m_stereoLink->setModel( &_ctl->m_stereoLinkModel );
	}

	connect( _ctl, SIGNAL( effectModelChanged( noemixerr::LadspaControls * ) ),
				this, SLOT( updateEffectView( noemixerr::LadspaControls * ) ),
							Qt::DirectConnection );
}


} // namespace noemixerr::gui
