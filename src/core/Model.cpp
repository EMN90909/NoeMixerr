// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Model.h"

namespace noemixerr
{

Model::Model(Model* parent, QString displayName, bool defaultConstructed) :
	QObject(parent),
	m_displayName(displayName),
	m_defaultConstructed(defaultConstructed)
{
}

bool Model::isDefaultConstructed() const
{
	return m_defaultConstructed;
}

Model* Model::parentModel() const
{
	return dynamic_cast<Model*>(parent());
}

QString Model::displayName() const
{
	return m_displayName;
}

void Model::setDisplayName(const QString& displayName)
{
	m_displayName = displayName;
}

QString Model::fullDisplayName() const
{
	const QString n = displayName();

	if (parentModel())
	{
		const QString p = parentModel()->fullDisplayName();

		if (!p.isEmpty())
		{
			return p + ">" + n;
		}
	}

	return n;
}



} // namespace noemixerr

