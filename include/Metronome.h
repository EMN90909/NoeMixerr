// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2024 saker
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_METRONOME_H
#define NoeMixerr_METRONOME_H

#include <cstddef>

namespace noemixerr {
class Metronome
{
public:
	bool active() const { return m_active; }
	void setActive(bool active) { m_active = active; }
	void processTick(int currentTick, int ticksPerBar, int beatsPerBar, size_t bufferOffset);

private:
	bool m_active = false;
};
} // namespace noemixerr

#endif // NoeMixerr_METRONOME_H
