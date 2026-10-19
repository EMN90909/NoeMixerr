// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2024-     Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_LFO_GRAPH_H
#define NoeMixerr_GUI_LFO_GRAPH_H

#include <QWidget>

#include "ModelView.h"
#include "embed.h"

namespace noemixerr
{

class EnvelopeAndLfoParameters;

namespace gui
{

class LfoGraph : public QWidget, public ModelView
{
	Q_OBJECT
	Q_PROPERTY(QColor noAmountColor MEMBER m_noAmountColor)
	Q_PROPERTY(QColor fullAmountColor MEMBER m_fullAmountColor)

public:
	LfoGraph(QWidget* parent);

protected:
	void mousePressEvent(QMouseEvent* me) override;
	void paintEvent(QPaintEvent* pe) override;

private:
	void drawInfoText(const EnvelopeAndLfoParameters&);
	void toggleAmountModel();

private:
	QPixmap m_lfoGraph = embed::getIconPixmap("lfo_graph");

	float m_randomGraph {0.};
	QColor m_noAmountColor;
	QColor m_fullAmountColor;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_LFO_GRAPH_H
