// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QDomElement>

#include "InlineAutomation.h"


namespace noemixerr
{

void InlineAutomation::saveSettings( QDomDocument & _doc,
							QDomElement & _parent )
{
	if( hasAutomation() )
	{
		QDomElement ap = _doc.createElement(
					AutomationClip::classNodeName() );
		QDomElement v = _doc.createElement( nodeName() );
		automationClip()->saveSettings( _doc, v );
		ap.appendChild( v );
		_parent.appendChild( ap );
	}
}




void InlineAutomation::loadSettings( const QDomElement & _this )
{
	QDomNode node = _this.namedItem( AutomationClip::classNodeName() );
	if( node.isElement() )
	{
		node = node.namedItem( nodeName() );
		if( node.isElement() )
		{
			automationClip()->loadSettings(
							node.toElement() );
		}
	}
}


} // namespace noemixerr