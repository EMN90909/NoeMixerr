// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_METER_MODEL_H
#define NoeMixerr_METER_MODEL_H

#include "AutomatableModel.h"

namespace noemixerr
{


class NOEMIXERR_EXPORT MeterModel : public Model
{
	Q_OBJECT
	mapPropertyFromModel(int,getNumerator,setNumerator,m_numeratorModel);
	mapPropertyFromModel(int,getDenominator,setDenominator,m_denominatorModel);
public:
	MeterModel( Model * _parent );
	~MeterModel() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _this,
						const QString & _name );
	void loadSettings( const QDomElement & _this, const QString & _name );

	void reset();

	// Must have the sub-models exposed to programmatically connect
	// to automation or controllers
	IntModel & numeratorModel()
	{
		return m_numeratorModel;
	}

	IntModel & denominatorModel()
	{
		return m_denominatorModel;
	}


private:
	IntModel m_numeratorModel;
	IntModel m_denominatorModel;

} ;


} // namespace noemixerr

#endif // NoeMixerr_METER_MODEL_H
