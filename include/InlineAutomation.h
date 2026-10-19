// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_INLINE_AUTOMATION_H
#define NoeMixerr_INLINE_AUTOMATION_H

#include "AutomationNode.h"
#include "AutomationClip.h"

namespace noemixerr
{

class InlineAutomation : public FloatModel
{
public:
	InlineAutomation() :
		FloatModel()
	{
	}

	InlineAutomation(const InlineAutomation& _copy) :
		FloatModel(_copy.value(), _copy.minValue(), _copy.maxValue(), _copy.step<float>()),
		m_autoClip(_copy.m_autoClip->clone())
	{
		m_autoClip->clearObjects();
		m_autoClip->addObject(this);
	}

	~InlineAutomation() override
	{
	}

	virtual float defaultValue() const = 0;

	bool hasAutomation() const
	{
		if( m_autoClip != nullptr && m_autoClip->getTimeMap().isEmpty() == false )
		{
			// Prevent saving inline automation if there's just one node at the beginning of
			// the clip, which has a InValue equal to the value of model (which is going
			// to be saved anyways) and no offset between the InValue and OutValue
			AutomationClip::timeMap::const_iterator firstNode =
				m_autoClip->getTimeMap().begin();

			if (isAtInitValue()
				&& m_autoClip->getTimeMap().size() == 1
				&& POS(firstNode) == 0
				&& INVAL(firstNode) == value()
				&& OFFSET(firstNode) == 0)
			{
				return false;
			}

			return true;
		}

		return false;
	}

	AutomationClip * automationClip()
	{
		if( m_autoClip == nullptr )
		{
			m_autoClip = std::make_unique<AutomationClip>(nullptr);
			m_autoClip->addObject( this );
		}
		return m_autoClip.get();
	}

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;


private:
	std::unique_ptr<AutomationClip> m_autoClip;

} ;


} // namespace noemixerr

#endif // NoeMixerr_INLINE_AUTOMATION_H
