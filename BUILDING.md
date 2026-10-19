# Building and validating NoeMixerr

NoeMixerr is a C++/Qt LMMS-derived DAW. Its large-scale identifier rebranding has not yet been validated across all platforms. These commands are reproduced by the build workflows. Successful *execution* of a CI job, not simply the existence of its workflow, is required for a platform to be supported.

## Shared prerequisites

- Git and submodule access to the publicly sourced third-party dependencies
- CMake 3.13 or later, C++20 toolchain, Ninja
- Qt 5 (Core, GUI, Widgets, XML, SVG, and tools)
- Development headers for libsndfile, libsamplerate, FFTW3 and supported audio backends

```sh
git clone --recurse-submodules https://github.com/EMN90909/NoeMixerr.git
cd NoeMixerr
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON -DWANT_SWH=OFF
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
```

## Ubuntu 24.04

```sh
sudo apt-get update
sudo apt-get install -y git cmake ninja-build build-essential pkg-config \
  qtbase5-dev qtbase5-private-dev qttools5-dev qttools5-dev-tools libqt5svg5-dev \
  libsndfile1-dev libfftw3-dev libsamplerate0-dev \
  libasound2-dev libpulse-dev libjack-jackd2-dev \
  libfltk1.3-dev libvorbis-dev libogg-dev libmpg123-dev liblist-moreutils-perl libxml-parser-perl
```

Then run the shared commands. See the [Linux CI workflow](.github/workflows/linux.yml).

## Windows

Use the MSYS2 UCRT64 shell, not Windows PowerShell, for the native MinGW toolchain. Install Git, Ninja, CMake, GCC and Qt5 components with pacman/pacboy, then use the shared commands. See the [Windows CI workflow](.github/workflows/windows.yml) for the dependency list and exact build invocation.

## macOS

```sh
brew install cmake ninja qt@5 libsndfile fftw libsamplerate pkg-config
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_TESTING=ON -DWANT_SWH=OFF -DCMAKE_PREFIX_PATH="$(brew --prefix qt@5)"
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
```

See the [macOS CI workflow](.github/workflows/macos.yml).

## Compatibility acceptance checklist

Compilation alone is insufficient for release. The following tests need real desktop/audio devices or fixtures:

1. Open an original LMMS `.mmp` file; confirm instruments, patterns and automation.
2. Save as `.mmp` / `.mmpz` and reopen, comparing notes, tempo and samples.
3. Play an arrangement, export audio, check duration and non-silence.
4. Import/export MIDI and check note timing.
5. Load bundled instruments, LV2/LADSPA where applicable, and scan optional VST components without crashing.
6. Confirm user configuration and sample paths migrate safely and don't overwrite existing LMMS user profiles.
7. Build and launch on Linux, Windows and macOS with the correct Qt plugins/resources.
8. Repeat with a clean clone and full submodule checkout.

These are **verification criteria**, not claims of tests already passed. Open issues in this repo for remaining failures, with sanitized logs.

## Licensing

All redistributed derivatives retain the original LMMS copyright and GPL-2.0-or-later source obligations. See `LICENSE.txt`, `doc/AUTHORS` and `doc/CONTRIBUTORS`.

CI disables the optional SWH LADSPA plugin suite to establish a portable baseline; enable it separately by installing the Perl XML parser and List::MoreUtils packages and configuring with `-DWANT_SWH=ON`. This does not remove existing SWH support.
