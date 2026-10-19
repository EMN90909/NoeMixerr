// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020 Martin Pavelek <he29.HS/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_KEYMAP_H
#define NoeMixerr_KEYMAP_H

#include <vector>
#include <QObject>
#include <QString>

#include "SerializingObject.h"

namespace noemixerr
{

class Keymap : public QObject, public SerializingObject
{
	Q_OBJECT
public:
	Keymap();
	Keymap(
		QString description,
		std::vector<int> newMap,
		int newFirst,
		int newLast,
		int newMiddle,
		int newBaseKey,
		float newBaseFreq
	);

	QString getDescription() const;
	void setDescription(QString description);

	int getMiddleKey() const {return m_middleKey;}
	int getFirstKey() const {return m_firstKey;}
	int getLastKey() const {return m_lastKey;}
	int getBaseKey() const {return m_baseKey;}
	float getBaseFreq() const {return m_baseFreq;}

	std::size_t getSize() const {return m_map.size();}

	//! @brief Return scale degree for a given key, based on current map and first/middle/last notes
	//! @param key MIDI key to be mapped
	//! @return Scale degree defined by the mapping on success, -1 if key isn't mapped
	int getDegree(int key) const;

	//! @brief Return octave offset for a given key, based on current map and the middle note
	//! @param key MIDI key to be mapped
	//! @return Octave offset defined by the mapping on success, 0 if key isn't mapped
	int getOctave(int key) const;

	const std::vector<int> &getMap() const {return m_map;}

	void saveSettings(QDomDocument &doc, QDomElement &element) override;
	void loadSettings(const QDomElement &element) override;
	inline QString nodeName() const override {return "keymap";}

private:
	QString m_description;          //!< name or description of the keymap

	std::vector<int> m_map;         //!< key to scale degree mapping
	int m_firstKey;                 //!< first key that will be mapped
	int m_lastKey;                  //!< last key that will be mapped
	int m_middleKey;                //!< first line of the map refers to this key
	int m_baseKey;                  //!< key which is assigned the reference "base note"
	float m_baseFreq;               //!< frequency of the base note (usually A4 @440 Hz)
};

} // namespace noemixerr

#endif // NoeMixerr_KEYMAP_H
