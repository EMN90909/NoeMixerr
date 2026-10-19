// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#include "noemixerrversion.h"
#include "AboutDialog.h"
#include "embed.h"
#include "versioninfo.h"


namespace noemixerr::gui
{

AboutDialog::AboutDialog(QWidget* parent) :
	QDialog(parent),
	Ui::AboutDialog()
{
	setupUi( this );


	iconLabel->setPixmap( embed::getIconPixmap( "icon", 64, 64 ) );

	versionLabel->setText( versionLabel->text().
					arg( NoeMixerr_VERSION ).
					arg( NoeMixerr_BUILDCONF_PLATFORM ).
					arg( NoeMixerr_BUILDCONF_MACHINE ).
					arg( QT_VERSION_STR ).
					arg( NoeMixerr_BUILDCONF_COMPILER_VERSION ) );
	versionLabel->setTextInteractionFlags(
					versionLabel->textInteractionFlags() |
					Qt::TextSelectableByMouse );

	copyrightLabel->setText( copyrightLabel->text().
					arg( NOEMIXERR_PROJECT_COPYRIGHT ) );

	authorLabel->setPlainText( embed::getText( "AUTHORS" ) );

	licenseLabel->setPlainText( embed::getText( "LICENSE.txt" ) );

	involvedLabel->setPlainText( embed::getText( "CONTRIBUTORS" ) );
}

} // namespace noemixerr::gui