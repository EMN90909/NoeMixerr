// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_INSTRUMENT_FUNCTIONS_H
#define NoeMixerr_INSTRUMENT_FUNCTIONS_H

#include <array>

#include "AutomatableModel.h"
#include "ComboBoxModel.h"
#include "JournallingObject.h"
#include "TempoSyncKnobModel.h"

namespace noemixerr
{

class InstrumentTrack;  // IWYU pragma: keep
class NotePlayHandle;

namespace gui
{

class InstrumentFunctionNoteStackingView;
class InstrumentFunctionArpeggioView;

}


class InstrumentFunctionNoteStacking : public Model, public JournallingObject
{
	Q_OBJECT

public:
	static const int MAX_CHORD_POLYPHONY = 13;
	static const int NUM_CHORD_TABLES = 95;

private:
	using ChordSemiTones = std::array<int8_t, MAX_CHORD_POLYPHONY>;

public:
	InstrumentFunctionNoteStacking( Model * _parent );
	~InstrumentFunctionNoteStacking() override = default;

	void processNote( NotePlayHandle* n );


	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;

	inline QString nodeName() const override
	{
		return "chordcreator";
	}


	struct Chord
	{
	private:
		QString m_name;
		ChordSemiTones m_semiTones;
		int m_size;

	public:
		Chord() : m_size( 0 ) {}

		Chord( const char * n, const ChordSemiTones & semi_tones );

		int size() const
		{
			return m_size;
		}

		bool isScale() const
		{
			return size() > 6;
		}

		bool isEmpty() const
		{
			return size() == 0;
		}

		bool hasSemiTone( int8_t semiTone ) const;

		int8_t last() const
		{
			return m_semiTones[size() - 1];
		}

		const QString & getName() const
		{
			return m_name;
		}

		int8_t operator [] ( int n ) const
		{
			return m_semiTones[n];
		}
	};


	struct ChordTable
	{
	private:
		ChordTable();

		struct Init
		{
			const char * m_name;
			ChordSemiTones m_semiTones;
		};

		static std::array<Init, NUM_CHORD_TABLES> s_initTable;
		std::vector<Chord> m_chords;

	public:
		static const ChordTable & getInstance()
		{
			static ChordTable inst;
			return inst;
		}

		const Chord & getByName( const QString & name, bool is_scale = false ) const;

		const Chord & getScaleByName( const QString & name ) const
		{
			return getByName( name, true );
		}

		const Chord & getChordByName( const QString & name ) const
		{
			return getByName( name, false );
		}

		const std::vector<Chord>& chords() const
		{
			return m_chords;
		}
	};


private:
	BoolModel m_chordsEnabledModel;
	ComboBoxModel m_chordsModel;
	FloatModel m_chordRangeModel;


	friend class gui::InstrumentFunctionNoteStackingView;

} ;




class InstrumentFunctionArpeggio : public Model, public JournallingObject
{
	Q_OBJECT
public:
	enum class ArpDirection
	{
		Up,
		Down,
		UpAndDown,
		DownAndUp,
		Random
	} ;

	InstrumentFunctionArpeggio( Model * _parent );
	~InstrumentFunctionArpeggio() override = default;

	void processNote( NotePlayHandle* n );


	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;

	inline QString nodeName() const override
	{
		return "arpeggiator";
	}


private:
	enum class ArpMode
	{
		Free,
		Sort,
		Sync
	} ;

	BoolModel m_arpEnabledModel;
	ComboBoxModel m_arpModel;
	FloatModel m_arpRangeModel;
	FloatModel m_arpRepeatsModel;
	FloatModel m_arpCycleModel;
	FloatModel m_arpSkipModel;
	FloatModel m_arpMissModel;
	TempoSyncKnobModel m_arpTimeModel;
	FloatModel m_arpGateModel;
	ComboBoxModel m_arpDirectionModel;
	ComboBoxModel m_arpModeModel;


	friend class InstrumentTrack;
	friend class gui::InstrumentFunctionArpeggioView;

} ;


} // namespace noemixerr

#endif // NoeMixerr_INSTRUMENT_FUNCTIONS_H
