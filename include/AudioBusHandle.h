// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2025 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_BUS_HANDLE_H
#define NoeMixerr_AUDIO_BUS_HANDLE_H

#include <memory>
#include <QString>
#include <QMutex>

#include "AudioBuffer.h"
#include "PlayHandle.h"

namespace noemixerr
{

class EffectChain;
class FloatModel;
class BoolModel;

/**
	@brief Job between @ref PlayHandle and @ref MixerChannel

	A @ref ThreadableJob class located at the exit point of each @ref PlayHandle into a @ref MixerChannel
	(or into an audio device, in case of AudioJack, but this is not supported in AudioBusHandle yet).
	It contains an optional @ref EffectChain which is e.g. visualized in the
	@ref gui::InstrumentTrackWindow or @ref gui::SampleTrackWindow.
	For processing, it adds all input play handles into an internal buffer,
	processes the @ref EffectChain (if existing) on that buffer
	and finally merges the buffer into its @ref MixerChannel.
*/
class AudioBusHandle : public ThreadableJob
{
public:
	AudioBusHandle(const QString& name, bool hasEffectChain = true,
		FloatModel* volumeModel = nullptr, FloatModel* panningModel = nullptr,
		BoolModel* mutedModel = nullptr);
	virtual ~AudioBusHandle();

	// indicate whether JACK & Co should provide output-buffer at ext. port
	bool extOutputEnabled() const { return m_extOutputEnabled; }
	void setExtOutputEnabled(bool enabled);

	// next mixer-channel after this audio-bus-handle
	// (-1 = none  0 = master)
	mix_ch_t nextMixerChannel() const { return m_nextMixerChannel; }
	void setNextMixerChannel(const mix_ch_t chnl) { m_nextMixerChannel = chnl; }

	const QString& name() const { return m_name; }
	void setName(const QString& newName);

	EffectChain* effects() { return m_effects.get(); }
	bool processEffects();

	// ThreadableJob stuff
	void doProcessing() override;
	bool requiresProcessing() const override { return true; }

	void addPlayHandle(PlayHandle* handle);
	void removePlayHandle(PlayHandle* handle);

	//! @returns true if the processing outputted corrupted audio (infs/nans).
	bool isCorrupted() const { return m_corrupted.load(std::memory_order_relaxed); }

private:
	volatile bool m_bufferUsage;

	AudioBuffer m_buffer;

	bool m_extOutputEnabled;
	mix_ch_t m_nextMixerChannel;

	QString m_name;

	std::unique_ptr<EffectChain> m_effects;

	PlayHandleList m_playHandles;
	QMutex m_playHandleLock;

	FloatModel* m_volumeModel;
	FloatModel* m_panningModel;
	BoolModel* m_mutedModel;
	
	std::atomic<bool> m_corrupted = false;

	friend class AudioEngine;
	friend class AudioEngineWorkerThread;
};

} // namespace noemixerr

#endif // NoeMixerr_AUDIO_BUS_HANDLE_H
