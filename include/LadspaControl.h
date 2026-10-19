// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_LADSPA_CONTROL_H
#define NoeMixerr_LADSPA_CONTROL_H

#include <ladspa.h>

#include "AutomatableModel.h"
#include "TempoSyncKnobModel.h"
#include "ValueBuffer.h"

namespace noemixerr
{

struct port_desc_t;

namespace gui
{

class LadspaControlView;
class LadspaMatrixControlDialog;

} // namespace gui


class NOEMIXERR_EXPORT LadspaControl : public Model, public JournallingObject
{
	Q_OBJECT
public:
	LadspaControl( Model * _parent, port_desc_t * _port,
							bool _link = false );
	~LadspaControl() override = default;

	LADSPA_Data value();
	ValueBuffer * valueBuffer();
	void setValue( LADSPA_Data _value );
	void setLink( bool _state );

	void linkControls( LadspaControl * _control );
	void unlinkControls( LadspaControl * _control );

	inline BoolModel * toggledModel()
	{
		return &m_toggledModel;
	}

	inline FloatModel * knobModel()
	{
		return &m_knobModel;
	}

	inline TempoSyncKnobModel * tempoSyncKnobModel()
	{
		return &m_tempoSyncKnobModel;
	}

	inline port_desc_t * port()
	{
		return m_port;
	}

	virtual void saveSettings( QDomDocument & _doc, QDomElement & _parent, const QString & _name );
	virtual void loadSettings( const QDomElement & _this, const QString & _name );
	inline QString nodeName() const override
	{
		return "port";
	}


signals:
	void changed( int _port, LADSPA_Data _value );
	void linkChanged( int _port, bool _state );


protected slots:
	void ledChanged();
	void knobChanged();
	void tempoKnobChanged();
	void linkStateChanged();

protected:
	void saveSettings( QDomDocument& doc, QDomElement& element ) override
	{
		Q_UNUSED(doc)
		Q_UNUSED(element)
	}

	void loadSettings( const QDomElement& element ) override
	{
		Q_UNUSED(element)
	}



private:
	bool m_link;
	port_desc_t * m_port;

	BoolModel m_linkEnabledModel;
	BoolModel m_toggledModel;
	FloatModel m_knobModel;
	TempoSyncKnobModel m_tempoSyncKnobModel;


	friend class gui::LadspaControlView;
	friend class gui::LadspaMatrixControlDialog;

} ;


} // namespace noemixerr

#endif // NoeMixerr_LADSPA_CONTROL_H
