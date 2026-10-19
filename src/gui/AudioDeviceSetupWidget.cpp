// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2015 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "AudioDeviceSetupWidget.h"

namespace noemixerr::gui
{

AudioDeviceSetupWidget::AudioDeviceSetupWidget(const QString & caption, QWidget * parent) :
	QGroupBox(QGroupBox::tr("Settings for %1").arg(tr(caption.toUtf8())), parent)
{
}

void AudioDeviceSetupWidget::show()
{
	parentWidget()->show();
	QWidget::show();
}

} // namespace noemixerr::gui
