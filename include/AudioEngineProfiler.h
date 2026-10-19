// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_AUDIO_ENGINE_PROFILER_H
#define NoeMixerr_AUDIO_ENGINE_PROFILER_H

#include <array>
#include <atomic>
#include <QFile>

#include "NoeMixerrTypes.h"
#include "MicroTimer.h"

namespace noemixerr
{

class AudioEngineProfiler
{
public:
	AudioEngineProfiler();
	~AudioEngineProfiler() = default;

	void startPeriod()
	{
		m_periodTimer.reset();
	}

	void finishPeriod( sample_rate_t sampleRate, f_cnt_t framesPerPeriod );

	int cpuLoad() const
	{
		return m_cpuLoad;
	}

	void setOutputFile( const QString& outputFile );

	enum class DetailType {
		NoteSetup,
		Instruments,
		Effects,
		Mixing,
		Count
	};

	constexpr static auto DetailCount = static_cast<std::size_t>(DetailType::Count);

	int detailLoad(const DetailType type) const
	{
		return m_detailLoad[static_cast<std::size_t>(type)].load(std::memory_order_relaxed);
	}

	class Probe
	{
	public:
		Probe(AudioEngineProfiler& profiler, AudioEngineProfiler::DetailType type)
			: m_profiler(profiler)
			, m_type(type)
		{
			profiler.startDetail(type);
		}
		~Probe() { m_profiler.finishDetail(m_type); }
		Probe& operator=(const Probe&) = delete;
		Probe(const Probe&) = delete;
		Probe(Probe&&) = delete;

	private:
		AudioEngineProfiler &m_profiler;
		const AudioEngineProfiler::DetailType m_type;
	};

private:
	void startDetail(const DetailType type) { m_detailTimer[static_cast<std::size_t>(type)].reset(); }
	void finishDetail(const DetailType type)
	{
		m_detailTime[static_cast<std::size_t>(type)] = m_detailTimer[static_cast<std::size_t>(type)].elapsed();
	}

	MicroTimer m_periodTimer;
	std::atomic<float> m_cpuLoad;
	QFile m_outputFile;

	// Use arrays to avoid dynamic allocations in realtime code
	std::array<MicroTimer, DetailCount> m_detailTimer;
	std::array<int, DetailCount> m_detailTime{0};
	std::array<std::atomic<float>, DetailCount> m_detailLoad{0};
};

} // namespace noemixerr

#endif // NoeMixerr_AUDIO_ENGINE_PROFILER_H
