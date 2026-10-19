// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_AUTOMATABLE_MODEL_VIEW_H
#define NoeMixerr_GUI_AUTOMATABLE_MODEL_VIEW_H

#include "ModelView.h"
#include "AutomatableModel.h"

class QMenu;
class QMouseEvent;

namespace noemixerr::gui
{

class NoeMixerr_EXPORT AutomatableModelView : public ModelView
{
public:
	AutomatableModelView( Model* model, QWidget* _this );
	~AutomatableModelView() override = default;

	// some basic functions for convenience
	AutomatableModel* modelUntyped()
	{
		return castModel<AutomatableModel>();
	}

	const AutomatableModel* modelUntyped() const
	{
		return castModel<AutomatableModel>();
	}

	void setModel( Model* model, bool isOldModelValid = true ) override;
	void unsetModel() override;

	template<typename T>
	inline T value() const
	{
		return modelUntyped() ? modelUntyped()->value<T>() : 0;
	}

	inline void setDescription( const QString& desc )
	{
		m_description = desc.trimmed();
	}

	inline void setUnit( const QString& unit )
	{
		m_unit = unit;
	}

	void addDefaultActions( QMenu* menu );

	void setConversionFactor( float factor );
	float getConversionFactor();


protected:
	virtual void mousePressEvent( QMouseEvent* event );

	QString m_description;
	QString m_unit;
	float m_conversionFactor; // Factor to be applied when the m_model->value is displayed
} ;




class AutomatableModelViewSlots : public QObject
{
	Q_OBJECT
public:
	AutomatableModelViewSlots( AutomatableModelView* amv, QObject* parent );

public slots:
	void execConnectionDialog();
	void removeConnection();

private slots:
	/// Copy the model's value to the clipboard.
	void copyToClipboard();
	/// Paste the model's value from the clipboard.
	void pasteFromClipboard();

protected:
	AutomatableModelView* m_amv;

} ;



template <typename ModelType> class NoeMixerr_EXPORT TypedModelView : public AutomatableModelView
{
public:
	TypedModelView( Model* model, QWidget* _this) :
		AutomatableModelView( model, _this )
	{}

	ModelType* model()
	{
		return castModel<ModelType>();
	}
	const ModelType* model() const
	{
		return castModel<ModelType>();
	}
};

using FloatModelView = TypedModelView<FloatModel>;
using IntModelView = TypedModelView<IntModel>;
using BoolModelView = TypedModelView<BoolModel>;

} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_AUTOMATABLE_MODEL_VIEW_H
