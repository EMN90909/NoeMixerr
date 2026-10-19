// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2013 Mike Choi <rdavidian71/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_VST_SYNC_DATA_H
#define NoeMixerr_VST_SYNC_DATA_H

namespace noemixerr
{


// VST sync frequency (in ms), how often will be VST plugin synced
// keep it power of two if possible (not used by now)
//#define VST_SNC_TIMER 1

// When defined, latency should be subtracted from song PPQ position
//#define VST_SNC_LATENCY



struct VstSyncData
{
	double ppqPos;
	int timeSigNumer;
	int timeSigDenom;
	bool isPlaying;
	bool isCycle;
	float cycleStart;
	float cycleEnd;
	bool playbackJumped;
	int bufferSize;
	int sampleRate;
	int bpm;

#ifdef VST_SNC_LATENCY
	float latency;
#endif
} ;


} // namespace noemixerr

#endif // NoeMixerr_VST_SYNC_DATA_H
