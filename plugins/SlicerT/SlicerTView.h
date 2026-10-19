// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Daniel Kauss Serna <daniel.kauss.serna@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_SLICERT_VIEW_H
#define NoeMixerr_GUI_SLICERT_VIEW_H


#include "InstrumentView.h"

class QPushButton;

namespace noemixerr {

class SlicerT;

namespace gui {

class ComboBox;
class Knob;
class LcdSpinBox;
class PixmapButton;
class SlicerTWaveform;

class SlicerTView : public InstrumentView
{
	Q_OBJECT

public slots:
	void exportMidi();
	void openFiles();
	void clearSlices();

public:
	SlicerTView(SlicerT* instrument, QWidget* parent);

	static constexpr int s_textBoxHeight = 20;
	static constexpr int s_textBoxWidth = 50;

	static constexpr int s_topBarHeight = 50;
	static constexpr int s_bottomBoxHeight = 97;
	static constexpr int s_bottomBoxOffset = 65;
	static constexpr int s_sampleBoxHeight = 14;
	static constexpr int s_folderButtonWidth = 15;
	static constexpr int s_leftBoxWidth = 400;


	static constexpr int s_x1 = 35;
	static constexpr int s_x2 = 85;
	static constexpr int s_x3 = 160;
	static constexpr int s_x4 = 190;
	static constexpr int s_x5 = 275;
	static constexpr int s_x6 = 325;
protected:
	void dragEnterEvent(QDragEnterEvent* dee) override;
	void dropEvent(QDropEvent* de) override;

	void paintEvent(QPaintEvent* pe) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	bool isResizable() const override { return true; }

	SlicerT* m_slicerTParent;

	Knob* m_noteThresholdKnob;
	Knob* m_fadeOutKnob;
	LcdSpinBox* m_bpmBox;
	ComboBox* m_snapSetting;
	PixmapButton* m_syncToggle;
	PixmapButton* m_clearButton;
	PixmapButton* m_folderButton;

	QPushButton* m_resetButton;
	QPushButton* m_midiExportButton;

	SlicerTWaveform* m_wf;

	Knob* createStyledKnob();

	QPixmap m_fullLogo;
	QPixmap m_background;


	int m_y1;
	int m_y2;
};
} // namespace gui
} // namespace noemixerr
#endif // NoeMixerr_GUI_SLICERT_VIEW_H
