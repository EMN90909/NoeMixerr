// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_ENGINE_H
#define NoeMixerr_ENGINE_H

#include <QString>
#include <QObject>

#include "noemixerrconfig.h"
#include "noemixerr_export.h"
#include "NoeMixerrTypes.h"

namespace noemixerr
{

class AudioEngine;
class Mixer;
class PatternStore;
class ProjectJournal;
class Song;
class Ladspa2NoeMixerr;

namespace gui
{
class GuiApplication;
}


class NoeMixerr_EXPORT Engine : public QObject
{
	Q_OBJECT
public:
	static void init( bool renderOnly );
	static void destroy();

	// core
	static AudioEngine *audioEngine()
	{
		return s_audioEngine;
	}

	static Mixer * mixer()
	{
		return s_mixer;
	}

	static Song * getSong()
	{
		return s_song;
	}

	static PatternStore * patternStore()
	{
		return s_patternStore;
	}

	static ProjectJournal * projectJournal()
	{
		return s_projectJournal;
	}

#ifdef NoeMixerr_HAVE_LV2
	static class Lv2Manager * getLv2Manager()
	{
		return s_lv2Manager;
	}
#endif

	static Ladspa2NoeMixerr * getLADSPAManager()
	{
		return s_ladspaManager;
	}

	static float framesPerTick()
	{
		return s_framesPerTick;
	}

	static float framesPerTick(sample_rate_t sample_rate);

	static void updateFramesPerTick();

	static inline Engine * inst()
	{
		if( s_instanceOfMe == nullptr )
		{
			s_instanceOfMe = new Engine();
		}
		return s_instanceOfMe;
	}

	static void setDndPluginKey(void* newKey);
	static void* pickDndPluginKey();

signals:
	void initProgress(const QString &msg);


private:
	// small helper function which sets the pointer to NULL before actually deleting
	// the object it refers to
	template<class T>
	static inline void deleteHelper(T** ptr)
	{
		T* tmp = *ptr;
		*ptr = nullptr;
		delete tmp;
	}

	static float s_framesPerTick;

	// core
	static AudioEngine *s_audioEngine;
	static Mixer * s_mixer;
	static Song * s_song;
	static PatternStore * s_patternStore;
	static ProjectJournal * s_projectJournal;

#ifdef NoeMixerr_HAVE_LV2
	static class Lv2Manager* s_lv2Manager;
#endif
	static Ladspa2NoeMixerr* s_ladspaManager;
	static void* s_dndPluginKey;

	// even though most methods are static, an instance is needed for Qt slots/signals
	static Engine* s_instanceOfMe;

	friend class gui::GuiApplication;
};


} // namespace noemixerr

#endif // NoeMixerr_ENGINE_H
