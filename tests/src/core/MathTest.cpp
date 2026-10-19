// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QObject>
#include <QtTest>

#include "noemixerr_math.h"

class MathTest : public QObject
{
	Q_OBJECT
private slots:
	void NumDigitsTest()
	{
		using namespace noemixerr;
		QCOMPARE(numDigitsAsInt(1.f), 1);
		QCOMPARE(numDigitsAsInt(9.9f), 2);
		QCOMPARE(numDigitsAsInt(10.f), 2);
		QCOMPARE(numDigitsAsInt(0.f), 1);
		QCOMPARE(numDigitsAsInt(-100.f), 4);
		QCOMPARE(numDigitsAsInt(-99.f), 3);
		QCOMPARE(numDigitsAsInt(-0.4f), 1); // there is no "-0" for LED spinbox
		QCOMPARE(numDigitsAsInt(-0.99f), 2);
		QCOMPARE(numDigitsAsInt(1000000000), 10);
		QCOMPARE(numDigitsAsInt(-1000000000), 11);
		QCOMPARE(numDigitsAsInt(900000000), 9);
		QCOMPARE(numDigitsAsInt(-900000000), 10);
	}
};

QTEST_GUILESS_MAIN(MathTest)
#include "MathTest.moc"
