<div align="center">

<img src="assets/noemixerr-logo.svg" alt="NoeMixerr logo" width="96">

# NoeMixerr

**Native C++ digital audio workstation, maintained by Noethric.**

[Source & issues](https://github.com/EMN90909/NoeMixerr) · [Releases](https://github.com/EMN90909/NoeMixerr/releases) · [Builds](https://github.com/EMN90909/NoeMixerr/actions) · [Contribute](https://github.com/EMN90909/NoeMixerr/issues/new)

![Linux CI](https://github.com/EMN90909/NoeMixerr/actions/workflows/linux.yml/badge.svg)
![Windows CI](https://github.com/EMN90909/NoeMixerr/actions/workflows/windows.yml/badge.svg)
![macOS CI](https://github.com/EMN90909/NoeMixerr/actions/workflows/macos.yml/badge.svg)

</div>

## Overview

NoeMixerr is a rebranded and modified derivative of **LMMS**, with the inherited C++ audio engine, song editor, pattern editor, piano roll, mixer, instruments and automation system. Some features depend on platform-specific dependencies. NoeMixerr is **not** currently a verified production release; the mechanical rename requires compatibility testing.

**Versioning:** NoeMixerr starts at **0.1.0-dev**. Pre-1.0 versions do not promise stable APIs or file formats. The inherited LMMS version and copyright history remain credited separately, not passed off as a new Noethric implementation.

## Build and test

See [BUILDING.md](BUILDING.md) for Linux, Windows and macOS prerequisites, CMake commands, known blockers and verification steps. CI builds are in [GitHub Actions](https://github.com/EMN90909/NoeMixerr/actions).

## Existing functionality

- Piano roll, pattern editing and multitrack song arrangement
- Synths, effects, SoundFont and audio file workflows
- Mixer channels, automation and MIDI import/export
- LMMS-compatible project workflows where verified

**Development modules:** [NoeAI local C++ MCP server](tools/noeai/README.md) supports read-only project inspection and previewed tempo, MIDI note, instrument-track, pattern and mixer edits, including up to 256 notes per transaction. Changes are atomically saved with backups when explicitly enabled; external MCP hosts must provide human approval. The [optional native audio recorder](tools/recorder/README.md) captures microphone/interface input through PortAudio into WAV files using a preallocated callback ring and separate disk writer. It is currently a standalone utility; imported takes are handled through the DAW.

**Work in progress:** integrated recording/monitoring/overdubbing, production-grade CLAP/VST3 hosting, in-editor AI agent UI, game-audio bridge, advanced buses, track freeze and other professional workflows are not yet complete. Rebranding alone does not implement them.

**Compatibility and audio testing:** CI exercises C++ unit tests, legacy LMMS project upgrading/reopening, and headless WAV rendering. The optional MCP and recording backends each have independent Linux and macOS CI. Build artifacts are development outputs, not signed or self-contained installers.

## Reporting problems

Please [open a NoeMixerr issue](https://github.com/EMN90909/NoeMixerr/issues/new), specifying your OS, NoeMixerr version, logs and a minimal reproduction without API keys or personal data.

## Original project and licensing

NoeMixerr is derived from [LMMS](https://github.com/LMMS/lmms). Original LMMS authors and contributors retain attribution and copyright. See [doc/AUTHORS](doc/AUTHORS), [doc/CONTRIBUTORS](doc/CONTRIBUTORS), source notices, and [LICENSE.txt](LICENSE.txt) for GPL-2.0-or-later terms and applicable third-party notices. Noethric maintains its modifications. Do not remove historical credits.

