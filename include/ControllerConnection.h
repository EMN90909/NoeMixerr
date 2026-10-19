// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Paul Giblock <pgllama/at/gmail.com>
// Copyright (c) 2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_CONTROLLER_CONNECTION_H
#define NoeMixerr_CONTROLLER_CONNECTION_H

#include <QObject>

#include "Controller.h"
#include "JournallingObject.h"
#include "ValueBuffer.h"

#include <vector>

namespace noemixerr
{

class ControllerConnection;

namespace gui
{
class ControllerConnectionDialog;
}

using ControllerConnectionVector = std::vector<ControllerConnection*>;

class NOEMIXERR_EXPORT ControllerConnection : public QObject, public JournallingObject
{
	Q_OBJECT
public:

	ControllerConnection(Controller * _controller);
	ControllerConnection( int _controllerId );

	~ControllerConnection() override;

	inline Controller * getController()
	{
		return m_controller;
	}

	void setController( Controller * _controller );

	inline void setController( int _controllerId );

	float currentValue( int _offset )
	{
		return m_controller->currentValue( _offset );
	}
	
	ValueBuffer * valueBuffer()
	{
		return m_controller->valueBuffer();
	}

	inline void setTargetName( const QString & _name );

	inline QString targetName() const
	{
		return m_targetName;
	}

	inline bool isFinalized()
	{
		return m_controllerId < 0;
	}

	static void finalizeConnections();

	void saveSettings( QDomDocument & _doc, QDomElement & _this ) override;
	void loadSettings( const QDomElement & _this ) override;

	static inline const QString classNodeName()
	{
		return "connection";
	}

	QString nodeName() const override
	{
		return classNodeName();
	}

public slots:
	void deleteConnection();

protected:
	//virtual controllerDialog * createDialog( QWidget * _parent );
	Controller * m_controller;
	QString m_targetName;
	int m_controllerId;
	
	bool m_ownsController;

	static ControllerConnectionVector s_connections;

signals:
	// The value changed while the audio engine isn't running (i.e: MIDI CC)
	void valueChanged();

	friend class gui::ControllerConnectionDialog;
};


} // namespace noemixerr

#endif // NoeMixerr_CONTROLLER_CONNECTION_H
