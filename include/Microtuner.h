// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020 Martin Pavelek <he29.HS/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MICROTUNER_H
#define NoeMixerr_MICROTUNER_H

#include "AutomatableModel.h"
#include "ComboBoxModel.h"
#include "JournallingObject.h"

namespace noemixerr
{

class NoeMixerr_EXPORT Microtuner : public Model, public JournallingObject
{
	Q_OBJECT
public:
	explicit Microtuner();

	bool enabled() const {return m_enabledModel.value();}
	bool keyRangeImport() const {return enabled() && m_keyRangeImportModel.value();}
	int currentScale() const {return m_scaleModel.value();}
	int currentKeymap() const {return m_keymapModel.value();}

	BoolModel *enabledModel() {return &m_enabledModel;}
	ComboBoxModel *scaleModel() {return &m_scaleModel;}
	ComboBoxModel *keymapModel() {return &m_keymapModel;}
	BoolModel *keyRangeImportModel() {return &m_keyRangeImportModel;}

	int firstKey() const;
	int lastKey() const;
	int baseKey() const;
	float baseFreq() const;

	//! @brief Return frequency for a given MIDI key, using the active mapping and scale.
	//! @param key A MIDI key number ranging from 0 to 127.
	//! @param userBaseNote The "A4" or "440 Hz" equivalent "base note". @see InstrumentTrack::baseNoteModel
	//! @return Frequency in Hz; 0 if key is out of range or not mapped.
	float keyToFreq(int key, int userBaseNote) const;

	int octaveSize() const;

	QString nodeName() const override {return "microtuner";}
	void saveSettings(QDomDocument & document, QDomElement &element) override;
	void loadSettings(const QDomElement &element) override;

protected slots:
	//! @brief Update scale name displayed in the microtuner scale list.
	//! @param index Index of the scale to update; update all scales if -1 or out of range.
	void updateScaleList(int index);

	//! @brief Update keymap name displayed in the microtuner scale list.
	//! @param index Index of the keymap to update; update all keymaps if -1 or out of range.
	void updateKeymapList(int index);

private:
	BoolModel m_enabledModel;               //!< Enable microtuner (otherwise using 12-TET @440 Hz)
	ComboBoxModel m_scaleModel;
	ComboBoxModel m_keymapModel;
	BoolModel m_keyRangeImportModel;

};

} // namespace noemixerr

#endif // NoeMixerr_MICROTUNER_H
