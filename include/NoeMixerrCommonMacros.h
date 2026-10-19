/*
 * NoeMixerrCommonMacros.h - defines some common macros used in the codebase
 *
 * Copyright (c) 2025 Roshan M R (Ross Maxx) <mrroshan127/at/gmail/dot/com>
 * 
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#ifndef NoeMixerr_COMMON_MACROS_H
#define NoeMixerr_COMMON_MACROS_H

namespace noemixerr
{

#define NoeMixerr_STRINGIFY(s) NoeMixerr_STR(s) // a macro used to stringify the plugin name
#define NoeMixerr_STR(PN) #PN

} // namespace noemixerr

#endif // NoeMixerr_COMMON_MACROS_H
