// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LADSPA_WIDGET_FACTORY_H
#define NoeMixerr_GUI_LADSPA_WIDGET_FACTORY_H


class QWidget;

namespace noemixerr
{

class LadspaControl;

namespace gui
{

class LadspaWidgetFactory
{
public:
	static QWidget * createWidget(LadspaControl * ladspaControl, QWidget * parent);
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_LADSPA_WIDGET_FACTORY_H
