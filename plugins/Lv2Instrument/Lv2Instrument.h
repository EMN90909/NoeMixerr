// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LV2_INSTRUMENT_H
#define LV2_INSTRUMENT_H

#include <QString>
#include <array>

#include "Instrument.h"
#include "InstrumentView.h"
#include "Lv2ControlBase.h"
#include "Lv2ViewBase.h"
#include "Note.h"

// whether to use MIDI vs playHandle
// currently only MIDI works
#define LV2_INSTRUMENT_USE_MIDI

namespace noemixerr
{

namespace gui
{

class Lv2InsView;

}

class Lv2Instrument : public Instrument, public Lv2ControlBase
{
	Q_OBJECT
signals:
	void modelChanged();
public:
	/*
		initialization
	*/
	Lv2Instrument(InstrumentTrack *instrumentTrackArg,
		 Descriptor::SubPluginFeatures::Key* key);
	~Lv2Instrument() override;
	void reload();
	void onSampleRateChanged();

	/*
		load/save
	*/
	void saveSettings(QDomDocument &doc, QDomElement &that) override;
	void loadSettings(const QDomElement &that) override;
	void loadFile(const QString &file) override;

	/*
		realtime funcs
	*/
	bool hasNoteInput() const override { return Lv2ControlBase::hasNoteInput(); }
#ifdef LV2_INSTRUMENT_USE_MIDI
	bool handleMidiEvent(const MidiEvent &event,
		const TimePos &time = TimePos(), f_cnt_t offset = 0) override;
#else
	void playNote(NotePlayHandle *nph, SampleFrame*) override;
#endif
	void play(SampleFrame* buf) override;

	/*
		misc
	*/
	gui::PluginView* instantiateView(QWidget *parent) override;

private slots:
	void updatePitchRange();

private:
	QString nodeName() const override;

#ifdef LV2_INSTRUMENT_USE_MIDI
	std::array<int, NumKeys> m_runningNotes = {};
#endif
	void clearRunningNotes();

	friend class gui::Lv2InsView;
};


namespace gui
{


class Lv2InsView : public InstrumentView, public Lv2ViewBase
{
Q_OBJECT
public:
	Lv2InsView(Lv2Instrument *_instrument, QWidget *_parent);

protected:
	void dragEnterEvent(QDragEnterEvent *_dee) override;
	void dropEvent(QDropEvent *_de) override;
	void hideEvent(QHideEvent* event) override;

private:
	void modelChanged() override;
};


} // namespace gui


} // namespace noemixerr

#endif // LV2_INSTRUMENT_H
