// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Dominic Clark
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Timeline.h"

#include <algorithm>
#include <tuple>

#include <QDomElement>

namespace noemixerr {

void Timeline::setLoopBegin(TimePos begin)
{
	std::tie(m_loopBegin, m_loopEnd) = std::minmax(begin, TimePos{m_loopEnd});
}

void Timeline::setLoopEnd(TimePos end)
{
	std::tie(m_loopBegin, m_loopEnd) = std::minmax(TimePos{m_loopBegin}, end);
}

void Timeline::setLoopPoints(TimePos begin, TimePos end)
{
	std::tie(m_loopBegin, m_loopEnd) = std::minmax(begin, end);
}

void Timeline::setLoopEnabled(bool enabled)
{
	if (enabled != m_loopEnabled) {
		m_loopEnabled = enabled;
		emit loopEnabledChanged(m_loopEnabled);
	}
}

void Timeline::setStopBehaviour(StopBehaviour behaviour)
{
	if (behaviour != m_stopBehaviour) {
		m_stopBehaviour = behaviour;
		emit stopBehaviourChanged(m_stopBehaviour);
	}
}

void Timeline::saveSettings(QDomDocument& doc, QDomElement& element)
{
	element.setAttribute("lp0pos", static_cast<int>(loopBegin()));
	element.setAttribute("lp1pos", static_cast<int>(loopEnd()));
	element.setAttribute("lpstate", static_cast<int>(loopEnabled()));
	element.setAttribute("stopbehaviour", static_cast<int>(stopBehaviour()));
}

void Timeline::loadSettings(const QDomElement& element)
{
	setLoopPoints(
		static_cast<TimePos>(element.attribute("lp0pos").toInt()),
		static_cast<TimePos>(element.attribute("lp1pos").toInt())
	);
	setLoopEnabled(static_cast<bool>(element.attribute("lpstate").toInt()));
	setStopBehaviour(static_cast<StopBehaviour>(element.attribute("stopbehaviour", "1").toInt()));
}

} // namespace noemixerr
