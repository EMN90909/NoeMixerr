// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2026 saker <sakertooth@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_TAP_TEMPO_H
#define NoeMixerr_TAP_TEMPO_H

#include <array>
#include <chrono>

#include "TapTempoView.h"
#include "ToolPlugin.h"

namespace noemixerr {

class TapTempo : public ToolPlugin
{
	Q_OBJECT
public:
	TapTempo();
	void tap(bool play);
	void sync();
	void reset();
	double bpm() const;

	QString nodeName() const override;
	void saveSettings(QDomDocument&, QDomElement&) override {}
	void loadSettings(const QDomElement&) override {}

	gui::PluginView* instantiateView(QWidget*) override { return new gui::TapTempoView(this); }

private:
	static constexpr auto MaxIntervals = 3;
	using clock = std::chrono::steady_clock;
	std::chrono::time_point<clock> m_lastTap;
	std::array<std::chrono::milliseconds, MaxIntervals> m_intervals;
	int m_beat = 0;
	int m_taps = 0;
	double m_bpm = 0;
};
} // namespace noemixerr

#endif // NoeMixerr_TAP_TEMPO_H
