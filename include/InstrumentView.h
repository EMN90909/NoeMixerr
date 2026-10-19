// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_INSTRUMENT_VIEW_H
#define NoeMixerr_GUI_INSTRUMENT_VIEW_H

#include "Instrument.h"
#include "PluginView.h"


namespace noemixerr::gui
{

class InstrumentTrackWindow;


//! Instrument view with variable size
class NOEMIXERR_EXPORT InstrumentView : public PluginView
{
public:
	InstrumentView( Instrument * _instrument, QWidget * _parent );
	~InstrumentView() override;

	Instrument * model()
	{
		return( castModel<Instrument>() );
	}

	const Instrument * model() const
	{
		return( castModel<Instrument>() );
	}

	void setModel( Model * _model, bool = false ) override;

	InstrumentTrackWindow * instrumentTrackWindow();

} ;




//! Instrument view with fixed NoeMixerr-default size
class NOEMIXERR_EXPORT InstrumentViewFixedSize : public InstrumentView
{
	QSize sizeHint() const override { return QSize(250, 250); }
	QSize minimumSizeHint() const override { return sizeHint(); }

public:
	using InstrumentView::InstrumentView;
	~InstrumentViewFixedSize() override = default;
} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_INSTRUMENT_VIEW_H
