// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIDI_CLIP_H
#define NoeMixerr_MIDI_CLIP_H

#include "Clip.h"
#include "Note.h"


namespace noemixerr
{


class InstrumentTrack;

namespace gui
{
class MidiClipView;
}


class NOEMIXERR_EXPORT MidiClip : public Clip
{
	Q_OBJECT
public:
	enum class Type
	{
		BeatClip,
		MelodyClip
	} ;

	MidiClip( InstrumentTrack* instrumentTrack );
	~MidiClip() override;

	void init();

	void updateLength() override;

	// note management
	Note * addNote( const Note & _new_note, const bool _quant_pos = true );

	NoteVector::const_iterator removeNote(NoteVector::const_iterator it);
	NoteVector::const_iterator removeNote(Note* note);

	Note * noteAtStep( int _step );

	void rearrangeAllNotes();
	void clearNotes();

	inline const NoteVector & notes() const
	{
		return m_notes;
	}

	Note * addStepNote( int step );
	void setStep( int step, bool enabled );

	//! Horizontally flip the positions of the given notes.
	void reverseNotes(const NoteVector& notes);

	// Split the list of notes on the given position
	void splitNotes(const NoteVector& notes, TimePos pos);

	// Split the list of notes along a line
	void splitNotesAlongLine(const NoteVector notes, TimePos pos1, int key1, TimePos pos2, int key2, bool deleteShortEnds);

	// clip-type stuff
	inline Type type() const
	{
		return m_clipType;
	}


	// next/previous track based on position in the containing track
	MidiClip * previousMidiClip() const;
	MidiClip * nextMidiClip() const;

	// settings-management
	void exportToXML(QDomDocument& doc, QDomElement& midiClipElement, bool onlySelectedNotes = false);
	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "midiclip";
	}

	inline InstrumentTrack * instrumentTrack() const
	{
		return m_instrumentTrack;
	}

	bool empty();


	gui::ClipView * createView( gui::TrackView * _tv ) override;

	MidiClip* clone() override
	{
		return new MidiClip(*this);
	}


	using Model::dataChanged;

public slots:
	void addSteps();
	void cloneSteps();
	void removeSteps();
	void clear();

protected:
	MidiClip( const MidiClip& other );
	void updatePatternTrack();

protected slots:
	void changeTimeSignature();


private:
	TimePos beatClipLength() const;

	void setType( Type _new_clip_type );
	void checkType();

	void resizeToFirstTrack();

	InstrumentTrack * m_instrumentTrack;

	Type m_clipType;

	// data-stuff
	NoteVector m_notes;
	int m_steps;

	MidiClip * adjacentMidiClipByOffset(int offset) const;

	friend class gui::MidiClipView;


signals:
	void destroyedMidiClip( noemixerr::MidiClip* );
} ;


} // namespace noemixerr

#endif // NoeMixerr_MIDI_CLIP_H
