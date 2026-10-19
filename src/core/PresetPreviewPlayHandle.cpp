// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include <QFileInfo>

#include "PresetPreviewPlayHandle.h"
#include "AudioEngine.h"
#include "Engine.h"
#include "Instrument.h"
#include "InstrumentTrack.h"
#include "PluginFactory.h"
#include "ProjectJournal.h"
#include "TrackContainer.h"

#include <atomic>

namespace noemixerr
{

// invisible track-container which is needed as parent for preview-channels
class PreviewTrackContainer : public TrackContainer
{
public:
	PreviewTrackContainer() :
		m_previewInstrumentTrack( nullptr ),
		m_previewNote( nullptr ),
		m_dataMutex()
	{
		setJournalling( false );
		m_previewInstrumentTrack = dynamic_cast<InstrumentTrack *>( Track::create( Track::Type::Instrument, this ) );
		m_previewInstrumentTrack->setJournalling( false );
		m_previewInstrumentTrack->setPreviewMode( true );
	}

	~PreviewTrackContainer() override = default;

	QString nodeName() const override
	{
		return "previewtrackcontainer";
	}

	InstrumentTrack* previewInstrumentTrack()
	{
		return m_previewInstrumentTrack;
	}

	NotePlayHandle* previewNote()
	{
		return m_previewNote.load(std::memory_order_acquire);
	}

	void setPreviewNote( NotePlayHandle * _note )
	{
		m_previewNote.store(_note, std::memory_order_release);
	}

	bool testAndSetPreviewNote( NotePlayHandle * expectedVal, NotePlayHandle * newVal )
	{
		return m_previewNote.compare_exchange_strong(expectedVal, newVal);
	}

	void lockData()
	{
		m_dataMutex.lock();
	}

	void unlockData()
	{
		m_dataMutex.unlock();
	}

	bool isPreviewing()
	{
		bool ret = !m_dataMutex.tryLock();
		if( ret == false )
		{
			m_dataMutex.unlock();
		}
		return ret;
	}


private:
	InstrumentTrack* m_previewInstrumentTrack;
	std::atomic<NotePlayHandle*> m_previewNote;
	QMutex m_dataMutex;

	friend class PresetPreviewPlayHandle;

} ;


PreviewTrackContainer * PresetPreviewPlayHandle::s_previewTC;



PresetPreviewPlayHandle::PresetPreviewPlayHandle( const QString & _preset_file, bool _load_by_plugin, DataFile *dataFile ) :
	PlayHandle( Type::PresetPreviewHandle ),
	m_previewNote(nullptr)
{
	setUsesBuffer( false );

	s_previewTC->lockData();

	Engine::audioEngine()->requestChangeInModel();
	s_previewTC->setPreviewNote( nullptr );
	s_previewTC->previewInstrumentTrack()->silenceAllNotes();
	Engine::audioEngine()->doneChangeInModel();

	const bool j = Engine::projectJournal()->isJournalling();
	Engine::projectJournal()->setJournalling( false );

	if( _load_by_plugin )
	{
		Instrument * i = s_previewTC->previewInstrumentTrack()->instrument();
		const QString ext = QFileInfo( _preset_file ).
							suffix().toLower();
		if( i == nullptr || !i->descriptor()->supportsFileType( ext ) )
		{
			const PluginFactory::PluginInfoAndKey& infoAndKey =
				getPluginFactory()->pluginSupportingExtension(ext);
			i = s_previewTC->previewInstrumentTrack()->
				loadInstrument(infoAndKey.info.name(), &infoAndKey.key);
		}
		if( i != nullptr )
		{
			i->loadFile( _preset_file );
		}
	}
	else
	{
		bool dataFileCreated = false;
		if( dataFile == 0 )
		{
			dataFile = new DataFile( _preset_file );
			dataFileCreated = true;
		}

		s_previewTC->previewInstrumentTrack()->loadTrackSpecificSettings(
					dataFile->content().firstChild().toElement());

		if( dataFileCreated )
		{
			delete dataFile;
		}
	}
	dataFile = 0;
	// make sure, our preset-preview-track does not appear in any MIDI-
	// devices list, so just disable receiving/sending MIDI-events at all
	s_previewTC->previewInstrumentTrack()->
				midiPort()->setMode( MidiPort::Mode::Disabled );

	Engine::audioEngine()->requestChangeInModel();
	// create note-play-handle for it
	m_previewNote = NotePlayHandleManager::acquire(
			s_previewTC->previewInstrumentTrack(), 0,
			std::numeric_limits<f_cnt_t>::max() / 2,
				Note( 0, 0, DefaultKey, 100 ) );

	setAudioBusHandle(s_previewTC->previewInstrumentTrack()->audioBusHandle());

	s_previewTC->setPreviewNote( m_previewNote );

	Engine::audioEngine()->addPlayHandle( m_previewNote );

	Engine::audioEngine()->doneChangeInModel();
	s_previewTC->unlockData();
	Engine::projectJournal()->setJournalling( j );
}




PresetPreviewPlayHandle::~PresetPreviewPlayHandle()
{
	Engine::audioEngine()->requestChangeInModel();
	// not muted by other preset-preview-handle?
	if (s_previewTC->testAndSetPreviewNote(m_previewNote, nullptr))
	{
		m_previewNote->noteOff();
	}
	Engine::audioEngine()->doneChangeInModel();
}




void PresetPreviewPlayHandle::play( SampleFrame* _working_buffer )
{
	// Do nothing; the preview instrument is played by m_previewNote, which
	// has been added to the audio engine
}




bool PresetPreviewPlayHandle::isFinished() const
{
	return m_previewNote->isMuted();
}




bool PresetPreviewPlayHandle::isFromTrack( const Track * _track ) const
{
	return s_previewTC && s_previewTC->previewInstrumentTrack() == _track;
}




void PresetPreviewPlayHandle::init()
{
	if( !s_previewTC )
	{
		s_previewTC = new PreviewTrackContainer;
	}
}




void PresetPreviewPlayHandle::cleanup()
{
	delete s_previewTC;
	s_previewTC = nullptr;
}




ConstNotePlayHandleList PresetPreviewPlayHandle::nphsOfInstrumentTrack(
						const InstrumentTrack * _it )
{
	ConstNotePlayHandleList cnphv;
	if( s_previewTC->previewNote() != nullptr &&
		s_previewTC->previewNote()->instrumentTrack() == _it )
	{
		cnphv.push_back( s_previewTC->previewNote() );
	}
	return cnphv;
}




bool PresetPreviewPlayHandle::isPreviewing()
{
	if (s_previewTC) {
		return s_previewTC->isPreviewing();
	}
	return false;
}


} // namespace noemixerr
