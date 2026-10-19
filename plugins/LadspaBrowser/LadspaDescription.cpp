// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "LadspaDescription.h"

#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include <QVBoxLayout>

#include "Engine.h"
#include "Ladspa2NoeMixerr.h"
#include "noemixerr_constants.h"


namespace noemixerr::gui
{


LadspaDescription::LadspaDescription( QWidget * _parent,
						LadspaPluginType _type ) :
	QWidget( _parent )
{
	Ladspa2NoeMixerr * manager = Engine::getLADSPAManager();

	l_sortable_plugin_t plugins;
	switch( _type )
	{
		case LadspaPluginType::Source:
			plugins = manager->getInstruments();
			break;
		case LadspaPluginType::Transfer:
			plugins = manager->getValidEffects();
			break;
		case LadspaPluginType::Valid:
			plugins = manager->getValidEffects();
			break;
		case LadspaPluginType::Invalid:
			plugins = manager->getInvalidEffects();
			break;
		case LadspaPluginType::Sink:
			plugins = manager->getAnalysisTools();
			break;
		case LadspaPluginType::Other:
			plugins = manager->getOthers();
			break;
		default:
			break;
	}

	QList<QString> pluginNames;
	for (const auto& plugin : plugins)
	{
		if (_type != LadspaPluginType::Valid || manager->getDescription(plugin.second)->inputChannels <= DEFAULT_CHANNELS)
		{
			pluginNames.push_back(plugin.first);
			m_pluginKeys.push_back(plugin.second);
		}
	}

	auto pluginsBox = new QGroupBox(tr("Plugins"), this);
	auto pluginList = new QListWidget(pluginsBox);
	pluginList->addItems( pluginNames );
	connect( pluginList, SIGNAL( currentRowChanged( int ) ),
						SLOT( rowChanged( int ) ) );
	connect( pluginList, SIGNAL( itemDoubleClicked( QListWidgetItem * ) ),
				SLOT( onDoubleClicked( QListWidgetItem * ) ) );
	( new QVBoxLayout( pluginsBox ) )->addWidget( pluginList );

	auto descriptionBox = new QGroupBox(tr("Description"), this);
	auto descriptionLayout = new QVBoxLayout(descriptionBox);
	descriptionLayout->setSpacing( 0 );
	descriptionLayout->setContentsMargins(0, 0, 0, 0);

	m_scrollArea = new QScrollArea( descriptionBox );
	descriptionLayout->addWidget( m_scrollArea );

	auto layout = new QVBoxLayout(this);
	layout->addWidget( pluginsBox );
	layout->addWidget( descriptionBox );

	if( pluginList->count() > 0 )
	{
		pluginList->setCurrentRow( 0 );
		m_currentSelection = m_pluginKeys[0];
		update( m_currentSelection );
	}
}




void LadspaDescription::update( const ladspa_key_t & _key )
{
	auto description = new QWidget;
	m_scrollArea->setWidget( description );

	auto layout = new QVBoxLayout(description);
	layout->setSizeConstraint( QLayout::SetFixedSize );

	Ladspa2NoeMixerr * manager = Engine::getLADSPAManager();

	auto name = new QLabel(description);
	name->setText(tr("Name: ") + manager->getName(_key));
	layout->addWidget( name );

	auto maker = new QLabel(description);
	maker->setText(tr("Maker: ") + manager->getMaker(_key));
	layout->addWidget( maker );

	auto copyright = new QLabel(description);
	copyright->setText(tr("Copyright: ") + manager->getCopyright(_key));
	layout->addWidget( copyright );

	auto requiresRealTime = new QLabel(description);
	requiresRealTime->setText(tr("Requires Real Time: ") +
				(manager->hasRealTimeDependency(_key) ? tr("Yes") : tr("No")));
	layout->addWidget( requiresRealTime );

	auto realTimeCapable = new QLabel(description);
	realTimeCapable->setText(tr("Real Time Capable: ") +
				(manager->isRealTimeCapable(_key) ? tr("Yes") : tr("No")));
	layout->addWidget( realTimeCapable );

	auto inplaceBroken = new QLabel(description);
	inplaceBroken->setText(tr("In Place Broken: ") +
				(manager->isInplaceBroken(_key) ? tr("Yes") : tr("No")));
	layout->addWidget( inplaceBroken );

	auto channelsIn = new QLabel(description);
	channelsIn->setText(tr("Channels In: ") + QString::number(
			manager->getDescription( _key )->inputChannels ) );
	layout->addWidget( channelsIn );

	auto channelsOut = new QLabel(description);
	channelsOut->setText(tr("Channels Out: ") + QString::number(
			manager->getDescription( _key )->outputChannels ) );
	layout->addWidget( channelsOut );
}




void LadspaDescription::rowChanged( int _pluginIndex )
{
	m_currentSelection = m_pluginKeys[_pluginIndex];
	update( m_currentSelection );
}




void LadspaDescription::onDoubleClicked( QListWidgetItem * _item )
{
	emit( doubleClicked( m_currentSelection ) );
}


} // namespace noemixerr::gui
