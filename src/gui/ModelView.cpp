// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QWidget>

#include "ModelView.h"

namespace noemixerr::gui
{


ModelView::ModelView( Model* model, QWidget* widget ) :
	m_widget( widget ),
	m_model( model )
{
}




ModelView::~ModelView()
{
	if( m_model != nullptr && m_model->isDefaultConstructed() )
	{
		delete m_model;
	}
}




void ModelView::setModel( Model* model, bool isOldModelValid )
{
	if( isOldModelValid && m_model != nullptr )
	{
		if( m_model->isDefaultConstructed() )
		{
			delete m_model;
		}
		else
		{
			m_model->disconnect( widget() );
		}
	}

	m_model = model;

	doConnections();

	widget()->update();

	modelChanged();
}




// Unsets the current model by setting a dummy empty model. The dummy model is marked as
// "defaultConstructed", so the next call to setModel will delete it.
void ModelView::unsetModel()
{
	setModel(new Model(nullptr, QString(), true));
}




void ModelView::doConnections()
{
	if( m_model != nullptr )
	{
		QObject::connect( m_model, SIGNAL(dataChanged()), widget(), SLOT(update()));
		QObject::connect( m_model, SIGNAL(propertiesChanged()), widget(), SLOT(update()));
	}
}


} // namespace noemixerr::gui
