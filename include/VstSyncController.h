// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2013 Mike Choi <rdavidian71/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_VST_SYNC_CONTROLLER_H
#define NoeMixerr_VST_SYNC_CONTROLLER_H

#include <QObject>

#include "SharedMemory.h"
#include "VstSyncData.h"  // IWYU pragma: keep

namespace noemixerr
{

class VstSyncController : public QObject
{
	Q_OBJECT
public:
	VstSyncController();

	void setAbsolutePosition(double ticks);
	void setPlaybackState(bool enabled);
	void setTempo(int newTempo);
	void setTimeSignature(int num, int denom);
	void startCycle(int startTick, int endTick);
	void stopCycle();
	void setPlaybackJumped(bool jumped);
	void update();

	const std::string& sharedMemoryKey() const noexcept { return m_syncData.key(); }

private slots:
	void updateSampleRate();

private:
	SharedMemory<VstSyncData> m_syncData;
};


} // namespace noemixerr

#endif // NoeMixerr_VST_SYNC_CONTROLLER_H
