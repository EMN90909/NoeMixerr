// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2015 Lukas W <lukaswhl/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "ProjectVersion.h"

#include <QtTest>

class ProjectVersionTest : public QObject
{
	Q_OBJECT
private slots:
	void ProjectVersionComparisonTests()
	{
		using namespace noemixerr;

		QVERIFY(ProjectVersion("1.1.0", ProjectVersion::CompareType::Minor) > "1.0.3");
		QVERIFY(ProjectVersion("1.1.0", ProjectVersion::CompareType::Major) < "2.1.0");
		QVERIFY(ProjectVersion("1.1.0", ProjectVersion::CompareType::Release) > "0.2.1");
		QVERIFY(ProjectVersion("1.1.4", ProjectVersion::CompareType::Release) < "1.1.10");
		QVERIFY(ProjectVersion("1.1.0", ProjectVersion::CompareType::Minor) == "1.1.5");
		QVERIFY( ! ( ProjectVersion("3.1.0", ProjectVersion::CompareType::Minor) < "2.2.5" ) );
		QVERIFY( ! ( ProjectVersion("2.5.0", ProjectVersion::CompareType::Release) < "2.2.5" ) );
		//A pre-release version has lower precedence than a normal version
		QVERIFY(ProjectVersion("1.1.0") > "1.1.0-alpha");
		//But higher precedence than the previous version
		QVERIFY(ProjectVersion("1.1.0-alpha") > "1.0.0");
		//Identifiers with letters or hyphens are compare lexically in ASCII sort order
		QVERIFY(ProjectVersion("1.1.0-alpha") < "1.1.0-beta");
		QVERIFY(ProjectVersion("1.2.0-rc1") < "1.2.0-rc2");
		//Build metadata MUST be ignored when determining version precedence
		QVERIFY(ProjectVersion("1.2.2") == "1.2.2+metadata");
		QVERIFY(ProjectVersion("1.0.0-alpha") < "1.0.0-alpha.1");
		QVERIFY(ProjectVersion("1.0.0-alpha.1") < "1.0.0-alpha.beta");
		QVERIFY(ProjectVersion("1.0.0-alpha.beta") < "1.0.0-beta");
		QVERIFY(ProjectVersion("1.0.0-beta.2") < "1.0.0-beta.11");
		//Test workaround for old, nonstandard version numbers
		QVERIFY(ProjectVersion("1.2.2.42") == "1.2.3-42");
		QVERIFY(ProjectVersion("1.2.2.42") > "1.2.2.21");
		//Ensure that newer versions of the same format aren't upgraded
		//in order to discourage use of incorrect versioning
		QVERIFY(ProjectVersion("1.2.3.42") == "1.2.3");
		//CompareVersion "All" should compare every identifier
		QVERIFY(
			ProjectVersion("1.0.0-a.b.c.d.e.f.g.h.i.j.k.l", ProjectVersion::CompareType::All)
			< "1.0.0-a.b.c.d.e.f.g.h.i.j.k.m"
		);
		//Prerelease identifiers may contain hyphens
		QVERIFY(ProjectVersion("1.0.0-Alpha-1.2") > "1.0.0-Alpha-1.1");
		//We shouldn't crash on invalid versions
		QVERIFY(ProjectVersion("1-invalid") == "1.0.0-invalid");
		QVERIFY(ProjectVersion("") == "0.0.0");
		//Numeric identifiers are smaller than non-numeric identiiers
		QVERIFY(ProjectVersion("1.0.0-alpha") > "1.0.0-1");
		//An identifier of the form "-x" is non-numeric, not negative
		QVERIFY(ProjectVersion("1.0.0-alpha.-1") > "1.0.0-alpha.1");
	}
};

QTEST_GUILESS_MAIN(ProjectVersionTest)
#include "ProjectVersionTest.moc"
