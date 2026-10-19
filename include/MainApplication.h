// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2017-2017 Tres Finocchiaro <tres.finocchiaro/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_MAIN_APPLICATION_H
#define NoeMixerr_GUI_MAIN_APPLICATION_H

#include "noemixerrconfig.h"

#include <QApplication>

#ifdef NoeMixerr_BUILD_WIN32
#include <windows.h>
#include <QAbstractNativeEventFilter>
#endif


namespace noemixerr::gui
{


#if defined(NoeMixerr_BUILD_WIN32)
class MainApplication : public QApplication, public QAbstractNativeEventFilter
#else
class MainApplication : public QApplication
#endif
{
public:
	MainApplication(int& argc, char** argv);
	bool event(QEvent* event) override;
#ifdef NoeMixerr_BUILD_WIN32
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
	using FilterResult = long;
#else
	using FilterResult = qintptr;
#endif // QT6 check
	bool win32EventFilter(MSG* msg, FilterResult* result);
	bool nativeEventFilter(const QByteArray& eventType, void* message, FilterResult* result);
#endif // NoeMixerr_BUILD_WIN32
	inline QString& queuedFile()
	{
	    return m_queuedFile;
	}
private:
	QString m_queuedFile;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_MAIN_APPLICATION_H
