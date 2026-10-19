// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_DUMMY_INSTRUMENT_H
#define NoeMixerr_DUMMY_INSTRUMENT_H

#include "Instrument.h"
#include "InstrumentView.h"
#include "Engine.h"

#include <cstring>

#include "AudioEngine.h"


namespace noemixerr
{


class DummyInstrument : public Instrument
{
public:
	DummyInstrument( InstrumentTrack * _instrument_track ) :
		Instrument( _instrument_track, nullptr )
	{
	}

	~DummyInstrument() override = default;

	void playNote( NotePlayHandle*, SampleFrame* buffer ) override
	{
		zeroSampleFrames(buffer, Engine::audioEngine()->framesPerPeriod());
	}

	void saveSettings( QDomDocument &, QDomElement & ) override
	{
	}

	void loadSettings( const QDomElement & ) override
	{
	}

	QString nodeName() const override
	{
		return "dummyinstrument";
	}

	gui::PluginView * instantiateView( QWidget * _parent ) override
	{
		return new gui::InstrumentViewFixedSize( this, _parent );
	}
} ;


} // namespace noemixerr

#endif // NoeMixerr_DUMMY_INSTRUMENT_H
