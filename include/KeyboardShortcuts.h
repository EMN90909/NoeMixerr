// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2025 Michael Gregorius
// Copyright (c) 2025 Tres Finocchiaro <tres.finocchiaro/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_KEYBOARDSHORTCUTS_H
#define NoeMixerr_KEYBOARDSHORTCUTS_H

#include "noemixerrconfig.h"

#include "qnamespace.h"


namespace noemixerr
{

// Qt on macOS maps:
//  - ControlModifier --> Command keys
//  - MetaModifier value --> Control keys
//  - Qt::AltModifier --> Option keys
//
// Our UI hints need to be adjusted to accommodate for this
constexpr const char* UI_CTRL_KEY =
#ifdef NoeMixerr_BUILD_APPLE
"⌘";
#else
"Ctrl";
#endif

constexpr const char* UI_ALT_KEY =
#ifdef NoeMixerr_BUILD_APPLE
"Option";
#else
"Alt";
#endif

// UI hint for copying OR linking a UI component
// this MUST be consistent with KBD_COPY_MODIFIER
constexpr const char* UI_COPY_KEY =
#ifdef NoeMixerr_BUILD_APPLE
UI_ALT_KEY;
#else
UI_CTRL_KEY;
#endif

// Shortcut for copying OR linking a UI component
// this MUST be consistent with UI_COPY_KEY
constexpr Qt::KeyboardModifier KBD_COPY_MODIFIER =
#ifdef NoeMixerr_BUILD_APPLE
Qt::AltModifier;
#else
Qt::ControlModifier;
#endif

} // namespace noemixerr

#endif // NoeMixerr_KEYBOARDSHORTCUTS_H
