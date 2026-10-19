// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_INSTRUMENT_PLAY_HANDLE_H
#define NoeMixerr_INSTRUMENT_PLAY_HANDLE_H

#include "PlayHandle.h"
#include "noemixerr_export.h"

namespace noemixerr
{

class Instrument;
class InstrumentTrack;

class NOEMIXERR_EXPORT InstrumentPlayHandle : public PlayHandle
{
public:
	InstrumentPlayHandle(Instrument * instrument, InstrumentTrack* instrumentTrack);

	~InstrumentPlayHandle() override = default;

	void play(SampleFrame* working_buffer) override;

	bool isFinished() const override
	{
		return false;
	}

	bool isFromTrack(const Track* track) const override;

private:
	Instrument* m_instrument;
};

} // namespace noemixerr

#endif // NoeMixerr_INSTRUMENT_PLAY_HANDLE_H
