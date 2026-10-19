// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Keratin
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <QtTest>
#include "Timeline.h"

#include "Song.h"

class TimelineTest : public QObject
{
	Q_OBJECT
public:
	bool positionChangedReceived;
	bool positionJumpedReceived;
	void resetReceived()
	{
		positionChangedReceived = false;
		positionJumpedReceived = false;
	}

private slots:
	void onPositionChanged() { positionChangedReceived = true; }
	void onPositionJumped() { positionJumpedReceived = true; }

private slots:

	void initTestCase()
	{
		using namespace noemixerr;
		Engine::init(true);
	}

	void cleanupTestCase()
	{
		using namespace noemixerr;
		Engine::destroy();
	}

	void JumpedTests()
	{
		using namespace noemixerr;

		Timeline timeline = Timeline();
		connect(&timeline, &Timeline::positionChanged, this, &TimelineTest::onPositionChanged);
		connect(&timeline, &Timeline::positionJumped, this, &TimelineTest::onPositionJumped);

		// By default, setting the ticks is treated as a forceful jump
		resetReceived();
		timeline.setTicks(10);
		QCOMPARE(timeline.ticks(), 10);
		QVERIFY(positionChangedReceived);
		QVERIFY(positionJumpedReceived);

		// However, using incrementTicks will not emit positionJumped.
		resetReceived();
		timeline.incrementTicks(10);
		QCOMPARE(timeline.ticks(), 20);
		QVERIFY(positionChangedReceived);
		QVERIFY(!positionJumpedReceived);
	}

	void ElapsedTimeTests()
	{
		using namespace noemixerr;

		Timeline timeline = Timeline();
		connect(&timeline, &Timeline::positionChanged, this, &TimelineTest::onPositionChanged);
		connect(&timeline, &Timeline::positionJumped, this, &TimelineTest::onPositionJumped);

		// Forecefully setting the ticks to 0 should reset the elapsed time
		timeline.setTicks(0);
		QCOMPARE(timeline.getElapsedSeconds(), 0);

		// Setting the ticks to a nonzero value should reset the elapsed time to that tick's time based on the current tempo
		Engine::getSong()->setTempo(240);
		double secondsPerTick = 60.0f / Engine::getSong()->getTempo() * 4 / DefaultTicksPerBar;
		timeline.setTicks(10);
		double initialElapsedSeconds = timeline.getElapsedSeconds();
		QCOMPARE(static_cast<int>(timeline.getElapsedSeconds() * 1000), static_cast<int>(10 * secondsPerTick * 1000)); // Rouding to milliseconds to prevent double comparison issues

		// Changing the tempo and then non-forcefully incrementing the ticks will increase the elapsed time based on the new tempo
		Engine::getSong()->setTempo(60);
		secondsPerTick = 60.0f / Engine::getSong()->getTempo() * 4 / DefaultTicksPerBar;
		timeline.incrementTicks(5);
		QCOMPARE(static_cast<int>(timeline.getElapsedSeconds() * 1000), static_cast<int>((initialElapsedSeconds + 5 * secondsPerTick) * 1000));

		// Forcefully setting the ticks (such as dragging the playhead with the mouse) will reset the elapsed time based on the global position and current tempo
		Engine::getSong()->setTempo(180);
		secondsPerTick = 60.0f / Engine::getSong()->getTempo() * 4 / DefaultTicksPerBar;
		timeline.setTicks(25);
		QCOMPARE(static_cast<int>(timeline.getElapsedSeconds() * 1000), static_cast<int>(25 * secondsPerTick * 1000));
	}

};

QTEST_GUILESS_MAIN(TimelineTest)
#include "TimelineTest.moc"
