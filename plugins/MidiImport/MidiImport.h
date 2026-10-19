// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _MIDI_IMPORT_H
#define _MIDI_IMPORT_H

#include <cstdint>
#include <QString>

#include "MidiEvent.h"
#include "ImportFilter.h"

namespace noemixerr
{


class MidiImport : public ImportFilter
{
	Q_OBJECT
public:
	MidiImport(const QString& file);
	~MidiImport() override = default;
	gui::PluginView* instantiateView(QWidget*) override { return nullptr; }

private:
	bool tryImport(TrackContainer* tc) override;
	bool readSMF(TrackContainer* tc);
	bool readRIFF(TrackContainer* tc);
	bool readTrack(int track_end, QString& track_name);
	void error();

	inline std::int32_t read32LE()
	{
		std::int32_t value = readByte();
		value |= readByte() << 8;
		value |= readByte() << 16;
		value |= readByte() << 24;
		return value;
	}

	inline std::int32_t readVar()
	{
		std::int32_t c = readByte();
		std::int32_t value = c & 0x7f;
		if (c & 0x80)
		{
			c = readByte();
			value = (value << 7) | (c & 0x7f);
			if (c & 0x80)
			{
				c = readByte();
				value = (value << 7) | (c & 0x7f);
				if (c & 0x80)
				{
					c = readByte();
					value = (value << 7) | c;
					if (c & 0x80) { return -1; }
				}
			}
		}
		return !file().atEnd() ? value : -1;
	}

	inline void skip(unsigned num_bytes) { while (num_bytes--) { readByte(); } }

	int m_timingDivision = 0;
};


} // namespace noemixerr

#endif
