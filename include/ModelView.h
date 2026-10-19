// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_MODEL_VIEW_H
#define NoeMixerr_GUI_MODEL_VIEW_H

#include <QPointer>
#include "Model.h"

namespace noemixerr::gui
{

class NoeMixerr_EXPORT ModelView
{
public:
	ModelView( Model* model, QWidget* widget );
	virtual ~ModelView();

	virtual void setModel( Model* model, bool isOldModelValid = true );
	virtual void unsetModel();

	Model* model()
	{
		return m_model;
	}

	const Model* model() const
	{
		return m_model;
	}

	template<class T>
	T* castModel()
	{
		return dynamic_cast<T*>( model() );
	}

	template<class T>
	const T* castModel() const
	{
		return dynamic_cast<const T*>( model() );
	}


protected:
	// sub-classes can re-implement this to track model-changes
	virtual void modelChanged()
	{
	}

	QWidget* widget()
	{
		return m_widget;
	}

	virtual void doConnections();


private:
	QWidget* m_widget;
	QPointer<Model> m_model;

} ;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_MODEL_VIEW_H
