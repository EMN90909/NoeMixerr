// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2024-     Michael Gregorius
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_ENVELOPE_GRAPH_H
#define NoeMixerr_GUI_ENVELOPE_GRAPH_H

#include <QWidget>

#include "ModelView.h"
#include "embed.h"

namespace noemixerr
{

class EnvelopeAndLfoParameters;

namespace gui
{

class EnvelopeGraph : public QWidget, public ModelView
{
	Q_OBJECT
	Q_PROPERTY(QColor noAmountColor MEMBER m_noAmountColor)
	Q_PROPERTY(QColor fullAmountColor MEMBER m_fullAmountColor)
	Q_PROPERTY(QColor markerFillColor MEMBER m_markerFillColor)
	Q_PROPERTY(QColor markerOutlineColor MEMBER m_markerOutlineColor)

public:
	enum class ScalingMode
	{
		Dynamic,
		Absolute,
		Relative
	};

public:
	EnvelopeGraph(QWidget* parent);

protected:
	void modelChanged() override;

	void mousePressEvent(QMouseEvent*) override;
	void contextMenuEvent(QContextMenuEvent*) override;
	void paintEvent(QPaintEvent*) override;

private:
	void toggleAmountModel();

private:
	QPixmap m_envGraph = embed::getIconPixmap("envelope_graph");

	EnvelopeAndLfoParameters* m_params = nullptr;

	ScalingMode m_scaling = ScalingMode::Dynamic;

	QColor m_noAmountColor;
	QColor m_fullAmountColor;
	QColor m_markerFillColor;
	QColor m_markerOutlineColor;
};

} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_GUI_ENVELOPE_GRAPH_H
