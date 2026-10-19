// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_EFFECT_CHAIN_H
#define NoeMixerr_EFFECT_CHAIN_H

#include "Model.h"
#include "SerializingObject.h"
#include "AutomatableModel.h"

namespace noemixerr
{

class AudioBuffer;
class Effect;

namespace gui
{

class EffectRackView;

} // namespace gui


class NOEMIXERR_EXPORT EffectChain : public Model, public SerializingObject
{
	Q_OBJECT
public:
	EffectChain( Model * _parent );
	~EffectChain() override;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;

	inline QString nodeName() const override
	{
		return "fxchain";
	}

	void appendEffect( Effect * _effect );
	void removeEffect( Effect * _effect );
	void moveDown( Effect * _effect );
	void moveUp( Effect * _effect );
	bool processAudioBuffer(AudioBuffer& buffer);

	void clear();


private:
	using EffectList = std::vector<Effect*>;
	EffectList m_effects;

	BoolModel m_enabledModel;


	friend class gui::EffectRackView;


signals:
	void aboutToClear();

} ;

} // namespace noemixerr

#endif // NoeMixerr_EFFECT_CHAIN_H
