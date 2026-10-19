// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2007-2008 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.



#ifndef PATMAN_H
#define PATMAN_H

#include "Instrument.h"
#include "InstrumentView.h"
#include "Sample.h"
#include "AutomatableModel.h"

namespace noemixerr
{

namespace gui
{
class PixmapButton;
class PatmanView;
} // namespace gui


#define MODES_16BIT	( 1 << 0 )
#define MODES_UNSIGNED	( 1 << 1 )
#define MODES_LOOPING	( 1 << 2 )
#define MODES_PINGPONG	( 1 << 3 )
#define MODES_REVERSE	( 1 << 4 )
#define MODES_SUSTAIN	( 1 << 5 )
#define MODES_ENVELOPE	( 1 << 6 )
#define MODES_CLAMPED	( 1 << 7 )


class PatmanInstrument : public Instrument
{
	Q_OBJECT
public:
	PatmanInstrument( InstrumentTrack * _track );
	~PatmanInstrument() override;

	void playNote( NotePlayHandle * _n,
						SampleFrame* _working_buffer ) override;
	void deleteNotePluginData( NotePlayHandle * _n ) override;


	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;

	void loadFile( const QString & _file ) override;

	QString nodeName() const override;

	float desiredReleaseTimeMs() const override
	{
		return 3.f;
	}

	gui::PluginView* instantiateView( QWidget * _parent ) override;


public slots:
	void setFile( const QString & _patch_file, bool _rename = true );


private:
	struct handle_data
	{
		Sample::PlaybackState* state;
		bool tuned;
		std::shared_ptr<Sample> sample;
	};

	QString m_patchFile;
	QVector<std::shared_ptr<Sample>> m_patchSamples;
	BoolModel m_loopedModel;
	BoolModel m_tunedModel;


	enum class LoadError
	{
		OK,
		Open,
		NotGUS,
		Instruments,
		Layers,
		IO
	} ;

	LoadError loadPatch( const QString & _filename );
	void unloadCurrentPatch();

	void selectSample( NotePlayHandle * _n );


	friend class gui::PatmanView;

signals:
	void fileChanged();

} ;


namespace gui
{


class PatmanView : public InstrumentViewFixedSize
{
	Q_OBJECT
public:
	PatmanView( Instrument * _instrument, QWidget * _parent );
	~PatmanView() override = default;


public slots:
	void openFile();
	void updateFilename();


protected:
	void dragEnterEvent( QDragEnterEvent * _dee ) override;
	void dropEvent( QDropEvent * _de ) override;
	void paintEvent( QPaintEvent * ) override;


private:
	void modelChanged() override;

	PatmanInstrument * m_pi;
	QString m_displayFilename;

	PixmapButton * m_openFileButton;
	PixmapButton * m_loopButton;
	PixmapButton * m_tuneButton;

} ;


} // namespace gui

} // namespace noemixerr

#endif // PATMAN_H
