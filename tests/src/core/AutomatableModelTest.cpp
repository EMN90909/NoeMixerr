// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019-2020 Johannes Lorenz <j.git$$$lorenz-ho.me, $$$=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include <QtTest>
#include "AutomatableModel.h"
#include "ComboBoxModel.h"
#include "Engine.h"

class AutomatableModelTest : public QObject
{
	Q_OBJECT
public:
	bool m1Changed, m2Changed;
	void resetChanged() { m1Changed = m2Changed = false; }

private slots: // helper slots
	void onM1Changed() { m1Changed = true; }
	void onM2Changed() { m2Changed = true; }

private slots: // tests
	//! Test that upcast and exact casts work,
	//! but no downcast or any other casts

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

	void CastTests()
	{
		using namespace noemixerr;

		ComboBoxModel comboModel;
		AutomatableModel* amPtr = &comboModel;
		QVERIFY(nullptr == amPtr->dynamicCast<FloatModel>()); // not a parent class
		QCOMPARE(&comboModel, amPtr->dynamicCast<AutomatableModel>()); // parent class
		QCOMPARE(&comboModel, amPtr->dynamicCast<IntModel>()); // parent class
		QCOMPARE(&comboModel, amPtr->dynamicCast<ComboBoxModel>()); // same class

		IntModel intModel;
		IntModel* imPtr = &intModel;
		QVERIFY(nullptr == imPtr->dynamicCast<FloatModel>()); // not a parent class
		QCOMPARE(&intModel, imPtr->dynamicCast<AutomatableModel>()); // parent class
		QCOMPARE(&intModel, imPtr->dynamicCast<IntModel>()); // same class
		QVERIFY(nullptr == imPtr->dynamicCast<ComboBoxModel>()); // child class
	}

	void LinkTests()
	{
		using namespace noemixerr;

		BoolModel m1(true), m2(false);

		QObject::connect(&m1, SIGNAL(dataChanged()),
			this, SLOT(onM1Changed()));
		QObject::connect(&m2, SIGNAL(dataChanged()),
			this, SLOT(onM2Changed()));

		resetChanged();
		m1.linkToModel(&m1);
		QVERIFY(!m1Changed); // cannot link to itself
		QVERIFY(!m2Changed);
		QVERIFY(m1.countLinks() == 0);

		resetChanged();
		m1.linkToModel(&m2);
		QVERIFY(m1.value() == m2.value()); // since m1 takes the value of m2
		QVERIFY(!m2Changed); // the second model is the source
		QVERIFY(m1.countLinks() == 1);

		resetChanged();
		m1.linkToModel(&m2);
		QVERIFY(!m1Changed); // it's already linked
		QVERIFY(!m2Changed);

		resetChanged();
		BoolModel m3(false);
		m1.setValue(1.f);
		m2.setValue(1.f);
		m1.linkToModel(&m2);
		QVERIFY(m1.value());
		QVERIFY(m2.value());
		QVERIFY(!m3.value());
		m2.linkToModel(&m3); // drag m3, drop on m2
		// m2 should take m3's (0) value
		QVERIFY(m2.value() == m3.value());
		QVERIFY(!m3.value());
		QVERIFY(m1.countLinks() == 2);
	}
};

QTEST_GUILESS_MAIN(AutomatableModelTest)
#include "AutomatableModelTest.moc"
