// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2009-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LOCAL_ZYNADDSUBFX_H
#define LOCAL_ZYNADDSUBFX_H

#include <array>

#include "Note.h"

class Master;
class NulEngine;

namespace noemixerr
{

class MidiEvent;
class SampleFrame;


class LocalZynAddSubFx
{

public:
	LocalZynAddSubFx();
	~LocalZynAddSubFx();

	void initConfig();

	void setSampleRate( int _sampleRate );
	void setBufferSize( int _bufferSize );

	void saveXML( const std::string & _filename );
	void loadXML( const std::string & _filename );

	void loadPreset( const std::string & _filename, int _part = 0 );

	void setPresetDir( const std::string & _dir );
	void setNoeMixerrWorkingDir( const std::string & _dir );

	void setPitchWheelBendRange( int semitones );

	void processMidiEvent( const MidiEvent& event );

	void processAudio( SampleFrame* _out );

	inline Master * master()
	{
		return m_master;
	}


protected:
	static int s_instanceCount;

	std::string m_presetsDir;

	std::array<int, NumKeys> m_runningNotes = {};
	Master * m_master;
	NulEngine* m_ioEngine;

} ;


} // namespace noemixerr

#endif
