# NoeMixerr

An original **C++20 digital audio workstation**, developed for the Noethric ecosystem and eventual NoeEngine integration. NoeStudio's arrangement, piano roll, mixer and dark workstation layout inform the design; the implementation is original rather than a copy of Futureboard's Rust/GPUI code.

## Current release: native DAW foundation

- Multitrack piano-roll sequencing: move between pitch rows and grid subdivisions, add/delete notes.
- Stereo instrument synthesizer with polyphonic sine/saw voices and note envelopes.
- Audio clips: import PCM WAV (16-bit mono/stereo), arrange on the timeline, mix with linear sample-rate conversion.
- Per-track gain, pan, mute and solo.
- Tempo-controlled playback using a Qt audio sink, plus offline WAV bounce.
- Native project files (`.noemix`) for notes and external WAV references.
- CMake, portable core regression tests and Linux/Windows/macOS CI.

**Status:** early functional workstation, **not yet full commercial DAW parity**. The C++ application is not a port of all Futureboard features. Missing: live recording, low-latency professional audio devices, VST3/CLAP hosting, buses/sends, complex DSP effects, automation editing, MIDI hardware import/export, time stretching, recovery/undo, portable media bundles and integrated NoeEngine editor panels. The playback engine currently renders a mix in memory before Qt playback; it is not a realtime plugin-safe callback.

## Build
Prerequisites: CMake >= 3.20, C++20 compiler, and Qt6 Widgets + Multimedia for desktop UI.

```sh
cmake -S . -B build -DNOEMIXERR_GUI=ON -DBUILD_TESTING=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/NoeMixerr
```

On Debian/Ubuntu: `sudo apt install cmake g++ qt6-base-dev qt6-multimedia-dev`.

## Workflow
Use **+ Track** to create a new instrument lane, double-click an arrangement lane to add a note, or double-click the piano roll to choose pitch and grid position. Right-click a piano note to delete it. Use **+ WAV** to attach an audio clip to a track. Adjust its gain, pan, mute and solo settings in the mixer. **Play** previews the mix. **Export WAV** bounces a stereo mix. **Open/Save** use `.noemix`.

## Design goals
C++ core and interface; native audio processing; deterministic exports; NoeEngine-friendly architecture; clean ownership boundaries; separate UI and DSP state; legitimate third-party license compliance. Qt must be redistributed according to its LGPL/commercial terms.

## Roadmap
1. Professional duplex audio backend, lock-free realtime graph, buffered recording and MIDI I/O.
2. Non-destructive audio editing, MIDI velocity controls, quantization, snap, piano-roll note dragging and undo/redo.
3. Routing matrix, buses, sends, effect graph, automation and stock DSP.
4. Sandboxed CLAP/VST3 support with plugin scanners and crash containment.
5. Portable project bundles, soundbanks, game-audio event authoring and NoeEngine embedded workflow.
6. Benchmarking and platform release packaging.

Copyright (c) 2026 Noethric. Original code: All rights reserved.
