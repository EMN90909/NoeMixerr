// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Dominic Clark
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_TIMELINE_H
#define NoeMixerr_TIMELINE_H

#include <QObject>

#include "AudioEngine.h"
#include "Engine.h"
#include "JournallingObject.h"
#include "TimePos.h"

namespace noemixerr {

class Timeline : public QObject, public JournallingObject
{
	Q_OBJECT

public:
	enum class StopBehaviour
	{
		BackToZero,
		BackToStart,
		KeepPosition
	};

	auto pos() const -> const TimePos& { return m_pos; }

	auto ticks() const -> tick_t { return m_pos.getTicks(); }

	//! Forcefully sets the current ticks, resets the frame offset, and sets the elapsed seconds based on the global position (ignoring potential mid-song tempo changes)
	//! Unless `jumped` is passed as false, this function will emit the `positionJumped` signal to allow other widgets to update accordingly.
	void setTicks(tick_t ticks, bool jumped = true)
	{
		m_pos.setTicks(ticks);
		m_frameOffset = 0;
		m_elapsedSeconds = ticks * Engine::framesPerTick() / Engine::audioEngine()->outputSampleRate();
		if (jumped) { emit positionJumped(); }
		emit positionChanged();
	}

	//! Advances the current timeline position by a certain number of ticks, in addition to updating the elapsed time based on the current tempo.
	void incrementTicks(tick_t increment)
	{
		m_pos.setTicks(ticks() + increment);
		m_elapsedSeconds += increment * Engine::framesPerTick() / Engine::audioEngine()->outputSampleRate();
		emit positionChanged();
	}

	auto frameOffset() const -> float { return m_frameOffset; }
	void setFrameOffset(const float frame) { m_frameOffset = frame; }

	auto loopBegin() const -> TimePos { return m_loopBegin; }
	auto loopEnd() const -> TimePos { return m_loopEnd; }
	auto loopEnabled() const -> bool { return m_loopEnabled; }

	void setLoopBegin(TimePos begin);
	void setLoopEnd(TimePos end);
	void setLoopPoints(TimePos begin, TimePos end);
	void setLoopEnabled(bool enabled);

	auto playStartPosition() const -> TimePos { return m_playStartPosition; }
	auto stopBehaviour() const -> StopBehaviour { return m_stopBehaviour; }

	void setPlayStartPosition(TimePos position) { m_playStartPosition = position; }
	void setStopBehaviour(StopBehaviour behaviour);

	auto getElapsedSeconds() const -> double { return m_elapsedSeconds + frameOffset() / Engine::audioEngine()->outputSampleRate(); }

	auto nodeName() const -> QString override { return "timeline"; }

signals:
	void loopEnabledChanged(bool enabled);
	void stopBehaviourChanged(noemixerr::Timeline::StopBehaviour behaviour);
	void positionChanged();
	void positionJumped();

protected:
	void saveSettings(QDomDocument& doc, QDomElement& element) override;
	void loadSettings(const QDomElement& element) override;

private:
	TimePos m_loopBegin = TimePos{0};
	TimePos m_loopEnd = TimePos{DefaultTicksPerBar};
	bool m_loopEnabled = false;
	TimePos m_pos = TimePos{0};

	float m_frameOffset = 0;

	double m_elapsedSeconds = 0;

	StopBehaviour m_stopBehaviour = StopBehaviour::BackToStart;
	TimePos m_playStartPosition = TimePos{-1};
};

} // namespace noemixerr

#endif // NoeMixerr_TIMELINE_H
