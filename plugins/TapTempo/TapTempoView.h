// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2026 saker <sakertooth@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TAP_TEMPO_VIEW_H
#define NoeMixerr_GUI_TAP_TEMPO_VIEW_H

#include "ToolPluginView.h"

class QCheckBox;
class QLabel;
class QPushButton;

namespace noemixerr {
class TapTempo;
}

namespace noemixerr::gui {

class TapTempoView : public ToolPluginView
{
	Q_OBJECT
public:
	TapTempoView(TapTempo* plugin);

private:
	void closeEvent(QCloseEvent*) override;
	void keyPressEvent(QKeyEvent*) override;
	void update();
	void reset();
	QPushButton* m_tapButton;
	QPushButton* m_resetButton;
	QPushButton* m_syncButton;
	QCheckBox* m_precisionCheckBox;
	QCheckBox* m_muteCheckBox;
	QLabel* m_msLabel;
	QLabel* m_hzLabel;
	TapTempo* m_plugin;
};
} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TAP_TEMPO_VIEW_H
