// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2026 saker <sakertooth@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "TapTempo.h"

#include <string>

#include "SamplePlayHandle.h"
#include "Song.h"
#include "embed.h"
#include "plugin_export.h"

namespace noemixerr {

extern "C" {
Plugin::Descriptor PLUGIN_EXPORT taptempo_plugin_descriptor
	= {NoeMixerr_STRINGIFY(PLUGIN_NAME), "Tap Tempo", QT_TRANSLATE_NOOP("PluginBrowser", "Tap to the beat"),
		"saker <sakertooth@gmail.com>", 0x0100, Plugin::Type::Tool, new PluginPixmapLoader("logo"), nullptr, nullptr};

PLUGIN_EXPORT Plugin* noemixerr_plugin_main(Model*, void*)
{
	return new TapTempo;
}
}

TapTempo::TapTempo()
	: ToolPlugin(&taptempo_plugin_descriptor, nullptr)
{
	m_intervals.fill(std::chrono::milliseconds::zero());
}

void TapTempo::tap(bool play)
{
	using namespace std::literals;

	if (play)
	{
		const auto metronomeFile = m_beat == 0 ? "misc/metronome02.ogg" : "misc/metronome01.ogg";
		Engine::audioEngine()->addPlayHandle(new SamplePlayHandle(metronomeFile));
	}

	m_beat = (m_beat + 1) % Engine::getSong()->getTimeSigModel().getNumerator();

	if (m_lastTap.time_since_epoch() == 0ms)
	{
		m_lastTap = clock::now();
		return;
	}

	const auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - m_lastTap);
	constexpr auto resetTime = 2000ms;

	if (delta >= resetTime)
	{
		m_bpm = 0;
		m_taps = 0;
		m_beat = 0;
		m_lastTap = clock::now();
		return;
	}

	m_intervals[(m_taps++) % MaxIntervals] = delta;

	constexpr auto millisecondsPerMinute = 60000.0;
	if (m_taps >= MaxIntervals)
	{
		// calculate the median of the stored intervals to reject outliers
		std::nth_element(m_intervals.begin(), m_intervals.begin() + m_intervals.size() / 2, m_intervals.end());
		const auto newBpm = millisecondsPerMinute / m_intervals[m_intervals.size() / 2].count();

		// use an adaptive EMA to smooth out jitter when in the ballpark and update quickly when moving to a new BPM
		const auto error = std::abs(newBpm - m_bpm);
		const auto alpha = std::clamp(error / 100.0, 0.2, 0.8);
		m_bpm = alpha * newBpm + (1.0 - alpha) * m_bpm;
	}
	else
	{
		// calculate the instant BPM for now until we have enough taps
		m_bpm = millisecondsPerMinute / delta.count();
	}

	m_lastTap = clock::now();
}

void TapTempo::sync()
{
	Engine::getSong()->setTempo(std::round(m_bpm));
}

void TapTempo::reset()
{
	m_bpm = 0;
	m_taps = 0;
	m_beat = 0;
	m_lastTap = std::chrono::time_point<clock>{};
}

QString TapTempo::nodeName() const
{
	return taptempo_plugin_descriptor.name;
}

double TapTempo::bpm() const
{
	return m_bpm;
}

} // namespace noemixerr
