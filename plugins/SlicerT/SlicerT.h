// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 Daniel Kauss Serna <daniel.kauss.serna@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_SLICERT_H
#define NoeMixerr_SLICERT_H

#include "AutomatableModel.h"
#include "ComboBoxModel.h"
#include "Instrument.h"
#include "Note.h"
#include "Sample.h"
#include "SlicerTView.h"

namespace noemixerr {

class SlicerT : public Instrument
{
	Q_OBJECT

public slots:
	void updateFile(QString file);
	void updateSlices();

signals:
	void isPlaying(float current, float start, float end);

public:
	SlicerT(InstrumentTrack* instrumentTrack);

	void playNote(NotePlayHandle* handle, SampleFrame* workingBuffer) override;
	void deleteNotePluginData(NotePlayHandle* handle) override;

	void saveSettings(QDomDocument& document, QDomElement& element) override;
	void loadSettings(const QDomElement& element) override;

	void loadFile(const QString& file) override;
	void findSlices();
	void findBPM();

	QString getSampleName() { return m_originalSample.sampleFile(); }

	QString nodeName() const override;
	gui::PluginView* instantiateView(QWidget* parent) override;

	std::vector<Note> getMidi();

private:
	FloatModel m_noteThreshold;
	FloatModel m_fadeOutFrames;
	IntModel m_originalBPM;
	ComboBoxModel m_sliceSnap;
	BoolModel m_enableSync;

	Sample m_originalSample;

	std::vector<float> m_slicePoints;

	InstrumentTrack* m_parentTrack;

	friend class gui::SlicerTView;
	friend class gui::SlicerTWaveform;
};
} // namespace noemixerr
#endif // NoeMixerr_SLICERT_H
