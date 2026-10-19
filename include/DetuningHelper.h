// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// Copyright (c) 2008-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_DETUNING_HELPER_H
#define NoeMixerr_DETUNING_HELPER_H

#include "InlineAutomation.h"

namespace noemixerr
{

class DetuningHelper : public InlineAutomation
{
	Q_OBJECT
public:
	DetuningHelper() :
		InlineAutomation()
	{
	}
	DetuningHelper(const DetuningHelper& _copy) :
		InlineAutomation(_copy)
	{
	}

	~DetuningHelper() override = default;

	float defaultValue() const override
	{
		return 0;
	}

	QString displayName() const override
	{
		return tr( "Note detuning" );
	}

	inline QString nodeName() const override
	{
		return "detuning";
	}

} ;


} // namespace noemixerr

#endif // NoeMixerr_DETUNING_HELPER_H
