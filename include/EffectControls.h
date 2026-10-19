// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_EFFECT_CONTROLS_H
#define NoeMixerr_EFFECT_CONTROLS_H

#include "Model.h"
#include "JournallingObject.h"
#include "Effect.h"

namespace noemixerr
{


namespace gui
{

class EffectControlDialog;

} // namespace gui

class EffectControls : public JournallingObject, public Model
{
public:
	EffectControls( Effect * _eff ) :
		JournallingObject(),
		Model( _eff ),
		m_effect( _eff ),
		m_viewVisible( false )
	{
	}

	~EffectControls() override = default;

	virtual int controlCount() = 0;
	virtual gui::EffectControlDialog * createView() = 0;


	void setViewVisible( bool _visible )
	{
		m_viewVisible = _visible;
	}

	bool isViewVisible() const
	{
		return m_viewVisible;
	}

	Effect * effect()
	{
		return m_effect;
	}


private:
	Effect * m_effect;
	bool m_viewVisible;

} ;


} // namespace noemixerr

#endif // NoeMixerr_EFFECT_CONTROLS_H
