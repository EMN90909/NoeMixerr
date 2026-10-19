// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_DUMMY_EFFECT_H
#define NoeMixerr_DUMMY_EFFECT_H

#include <QDomElement>

#include "Effect.h"
#include "EffectControls.h"
#include "EffectControlDialog.h"

namespace noemixerr
{

namespace gui
{

class Knob;


class DummyEffectControlDialog : public EffectControlDialog
{
public:
	DummyEffectControlDialog( EffectControls * _controls ) :
		EffectControlDialog( _controls )
	{
	}

} ;

} // namespace gui

class DummyEffectControls : public EffectControls
{
public:
	DummyEffectControls( Effect * _eff ) :
		EffectControls( _eff )
	{
	}

	~DummyEffectControls() override = default;

	int controlCount() override
	{
		return 0;
	}

	void saveSettings( QDomDocument &, QDomElement & ) override
	{
	}

	void loadSettings( const QDomElement & ) override
	{
	}

	QString nodeName() const override
	{
		return "DummyControls";
	}

	gui::EffectControlDialog * createView() override
	{
		return new gui::DummyEffectControlDialog( this );
	}
} ;



class DummyEffect : public Effect
{
	Q_OBJECT
public:
	DummyEffect( Model * _parent, const QDomElement& originalPluginData ) :
		Effect( nullptr, _parent, nullptr ),
		m_controls( this ),
		m_originalPluginData( originalPluginData )
	{
		setName();
		setDontRun(true);
	}

	~DummyEffect() override = default;

	EffectControls * controls() override
	{
		return &m_controls;
	}

	ProcessStatus processImpl(SampleFrame*, const f_cnt_t) override
	{
		return ProcessStatus::Sleep;
	}

	const QDomElement& originalPluginData() const
	{
		return m_originalPluginData;
	}



private:
	DummyEffectControls m_controls;
	const QDomElement m_originalPluginData;
	
	// Parse the display name from the dom
	virtual void setName()
	{
		QDomNodeList keys = originalPluginData().elementsByTagName( "key" );
		for( int i = 0; !keys.item( i ).isNull(); ++i )
		{
			QDomNodeList attributes = keys.item( i ).toElement().elementsByTagName( "attribute" );
			for( int j = 0; !attributes.item( j ).isNull(); ++j )
			{
				QDomElement attribute = attributes.item( j ).toElement();
				if( attribute.hasAttribute( "value" ) )
				{
					QString name = tr("NOT FOUND") + " (" + attribute.attribute( "value" ) + ")";
					setDisplayName(name);
					return;
				}

			}

		}
	}
} ;


} // namespace noemixerr

#endif // NoeMixerr_DUMMY_EFFECT_H
