// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2011-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QMenu>
#include <QMouseEvent>

#include "AutomatableModelView.h"
#include "AutomationClip.h"
#include "ControllerConnectionDialog.h"
#include "ControllerConnection.h"
#include "embed.h"
#include "GuiApplication.h"
#include "KeyboardShortcuts.h"
#include "MainWindow.h"
#include "StringPairDrag.h"
#include "Clipboard.h"

#include "AutomationEditor.h"


namespace noemixerr::gui
{

static float floatFromClipboard(bool* ok=nullptr);

AutomatableModelView::AutomatableModelView( Model* model, QWidget* _this ) :
	ModelView( model, _this ),
	m_conversionFactor( 1.0 )
{
	widget()->setAcceptDrops( true );
	widget()->setCursor(Qt::PointingHandCursor);
}

void AutomatableModelView::addDefaultActions( QMenu* menu )
{
	AutomatableModel* model = modelUntyped();

	auto amvSlots = new AutomatableModelViewSlots(this, menu);

	menu->addAction( embed::getIconPixmap( "reload" ),
						AutomatableModel::tr( "&Reset (%1%2)" ).
							arg( model->initValue<float>() * m_conversionFactor ).
							arg( m_unit ),
						model, SLOT(reset()));

	menu->addSeparator();
	menu->addAction( embed::getIconPixmap( "edit_copy" ),
						AutomatableModel::tr( "&Copy value (%1%2)" ).
							arg( model->value<float>() * m_conversionFactor ).
							arg( m_unit ),
						amvSlots, SLOT(copyToClipboard()));

	bool canPaste = true;
	const float valueToPaste = floatFromClipboard(&canPaste);
	const QString pasteDesc = canPaste ?
					AutomatableModel::tr( "&Paste value (%1%2)").
						arg( valueToPaste ).
						arg( m_unit )
					: AutomatableModel::tr( "&Paste value");
	QAction* pasteAction = menu->addAction( embed::getIconPixmap( "edit_paste" ),
						pasteDesc, amvSlots, SLOT(pasteFromClipboard()));
	pasteAction->setEnabled(canPaste);

	menu->addSeparator();

	if (model->isLinked())
	{
		menu->addAction(embed::getIconPixmap("edit_unlink"),
							AutomatableModel::tr("Remove all linked controls"),
							model, SLOT(unlink()));
		menu->addSeparator();
	}

	QString controllerTxt;
	if( model->controllerConnection() )
	{
		Controller* cont = model->controllerConnection()->getController();
		if( cont )
		{
			controllerTxt = AutomatableModel::tr( "Connected to %1" ).arg( cont->name() );
		}
		else
		{
			controllerTxt = AutomatableModel::tr( "Connected to controller" );
		}

		QMenu* contMenu = menu->addMenu( embed::getIconPixmap( "controller" ), controllerTxt );

		contMenu->addAction( embed::getIconPixmap( "controller" ),
								AutomatableModel::tr("Edit connection..."),
								amvSlots, SLOT(execConnectionDialog()));
		contMenu->addAction( embed::getIconPixmap( "cancel" ),
								AutomatableModel::tr("Remove connection"),
								amvSlots, SLOT(removeConnection()));
	}
	else
	{
		menu->addAction( embed::getIconPixmap( "controller" ),
							AutomatableModel::tr("Connect to controller..."),
							amvSlots, SLOT(execConnectionDialog()));
	}
}




void AutomatableModelView::setModel( Model* model, bool isOldModelValid )
{
	ModelView::setModel( model, isOldModelValid );
}




// Unsets the current model by setting a dummy empty model. The dummy model is marked as
// "defaultConstructed", so the next call to setModel will delete it.
void AutomatableModelView::unsetModel()
{
	if (dynamic_cast<FloatModelView*>(this))
	{
		setModel(new FloatModel(0, 0, 0, 1, nullptr, QString(), true));
	}
	else if (dynamic_cast<IntModelView*>(this))
	{
		setModel(new IntModel(0, 0, 0, nullptr, QString(), true));
	}
	else if (dynamic_cast<BoolModelView*>(this))
	{
		setModel(new BoolModel(false, nullptr, QString(), true));
	}
	else
	{
		ModelView::unsetModel();
	}
}




void AutomatableModelView::mousePressEvent( QMouseEvent* event )
{
	if (event->button() == Qt::LeftButton && event->modifiers() & KBD_COPY_MODIFIER)
	{
		new gui::StringPairDrag( "automatable_model", QString::number( modelUntyped()->id() ), QPixmap(), widget() );
		event->accept();
	}
	else if( event->button() == Qt::MiddleButton )
	{
		modelUntyped()->reset();
	}
}


void AutomatableModelView::setConversionFactor( float factor )
{
	if( factor != 0.0 )
	{
		m_conversionFactor = factor;
	}
}


float AutomatableModelView::getConversionFactor()
{
	return m_conversionFactor;
}


AutomatableModelViewSlots::AutomatableModelViewSlots( AutomatableModelView* amv, QObject* parent ) :
	QObject(),
	m_amv( amv )
{
	connect( parent, SIGNAL(destroyed()), this, SLOT(deleteLater()), Qt::QueuedConnection );
}




void AutomatableModelViewSlots::execConnectionDialog()
{
	// TODO[pg]: Display a dialog with list of controllers currently in the song
	// in addition to any system MIDI controllers
	AutomatableModel* m = m_amv->modelUntyped();

	m->displayName();
	gui::ControllerConnectionDialog d( getGUI()->mainWindow(), m );

	if( d.exec() == 1 )
	{
		// Actually chose something
		if( d.chosenController() )
		{
			// Update
			if( m->controllerConnection() )
			{
				m->controllerConnection()->setController( d.chosenController() );
			}
			// New
			else
			{
				auto cc = new ControllerConnection(d.chosenController());
				m->setControllerConnection( cc );
				//cc->setTargetName( m->displayName() );
			}
		}
		// no controller, so delete existing connection
		else
		{
			removeConnection();
		}
	}
}




void AutomatableModelViewSlots::removeConnection()
{
	AutomatableModel* m = m_amv->modelUntyped();

	if( m->controllerConnection() )
	{
		delete m->controllerConnection();
		m->setControllerConnection( nullptr );
	}
}




void AutomatableModelViewSlots::copyToClipboard()
{
	// For copyString() and MimeType enum class
	using namespace Clipboard;

	copyString( QString::number( m_amv->value<float>() * m_amv->getConversionFactor() ), MimeType::Default );
}

void AutomatableModelViewSlots::pasteFromClipboard()
{
	bool isNumber = false;
	const float number = floatFromClipboard(&isNumber);
	if (isNumber) {
		m_amv->modelUntyped()->setValue(number / m_amv->getConversionFactor());
	}
}

/// Attempt to parse a float from the clipboard
static float floatFromClipboard(bool* ok)
{
	// For getString() and MimeType enum class
	using namespace Clipboard;

	return getString( MimeType::Default ).toFloat(ok);
}


} // namespace noemixerr::gui
