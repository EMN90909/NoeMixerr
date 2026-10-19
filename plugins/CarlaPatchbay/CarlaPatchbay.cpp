// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (C) 2014-2018 Filipe Coelho <falktx@falktx.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Carla.h"

#include "embed.h"
#include "plugin_export.h"
#include "InstrumentTrack.h"

namespace noemixerr
{


extern "C"
{

Plugin::Descriptor PLUGIN_EXPORT carlapatchbay_plugin_descriptor =
{
    NoeMixerr_STRINGIFY( PLUGIN_NAME ),
    "Carla Patchbay",
    QT_TRANSLATE_NOOP( "PluginBrowser",
                       "Carla Patchbay Instrument" ),
    "falkTX <falktx/at/falktx.com>",
    CARLA_VERSION_HEX,
    Plugin::Type::Instrument,
    new PluginPixmapLoader( "logo" ),
    nullptr,
    nullptr,
} ;

PLUGIN_EXPORT Plugin* noemixerr_plugin_main(Model* m, void*)
{
    return new CarlaInstrument(static_cast<InstrumentTrack*>(m), &carlapatchbay_plugin_descriptor, true);
}

}


} // namespace noemixerr