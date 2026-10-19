// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 CYBERDEViLNL <cyberdevilnl/at/protonmail/dot/ch>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_COLOR_CHOOSER_H
#define NoeMixerr_GUI_COLOR_CHOOSER_H

#include <QApplication>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QVector>

namespace noemixerr::gui
{


class ColorChooser : public QColorDialog
{
public:
	ColorChooser(const QColor &initial, QWidget *parent): QColorDialog(initial, parent) {};
	ColorChooser(QWidget *parent): QColorDialog(parent) {};
	//! For getting a color without having to initialise a color dialog
	ColorChooser() = default;
	enum class Palette {Default, Track, Mixer};
	//! Set global palette via array, checking bounds
	void setPalette (QVector<QColor>);
	//! Set global paletter via enum
	void setPalette (Palette);
	//! Set palette via enum, return self pointer for chaining
	ColorChooser* withPalette (Palette);
	//! Return a certain palette
	static QVector<QColor> getPalette (Palette);

protected:
	//! Forward key events to the parent to prevent stuck notes when the dialog gets focus
	void keyReleaseEvent(QKeyEvent *event) override
	{
		QApplication::sendEvent(parentWidget(), event);
	}
private:
	//! Copy the current QColorDialog palette into an array
	static QVector<QColor> defaultPalette();
	//! Generate a nice palette, with adjustable value
	static QVector<QColor> nicePalette (int);
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_COLOR_CHOOSER_H
