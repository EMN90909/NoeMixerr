# NoeMixerr native audio capture (preview)

This optional C++20/PortAudio utility records from the operating system's **default
audio input** to 16-bit PCM WAV. It is designed as a recording backend for a future
NoeMixerr arrangement/audio-track integration, rather than a replacement for the DAW
audio engine. Currently recording, overdubbing and take management are **not embedded**
in the workstation interface.

The PortAudio callback writes into a preallocated single-producer/single-consumer ring.
A separate thread performs disk I/O. The file is first written to a `.partial` path
and published only after completing the RIFF header and checking for overruns.

## Dependencies and build

Linux: `sudo apt install cmake g++ pkg-config portaudio19-dev`.

macOS: `brew install cmake pkg-config portaudio`.

```sh
cmake -S tools/recorder -B build-recorder -DCMAKE_BUILD_TYPE=Release
cmake --build build-recorder --parallel
./build-recorder/noemixerr-recorder --devices
./build-recorder/noemixerr-recorder --output take.wav --seconds 15 --rate 48000 --channels 2
```

A supported input device and microphone/audio-interface permission are required.
Import `take.wav` through NoeMixerr's sample/audio-track facilities. Recording
does not read, rewrite or update projects on its own.

## Device-free smoke check

```sh
./build-recorder/noemixerr-recorder --self-test ./capture-test.wav
```

Generates a deterministic stereo test tone without opening an audio device.
The actual device capture path requires manual verification on each target OS.

Limitations: default device only, no input monitoring, no punch recording,
no takes, no drop-in engine integration, and no plugin latency compensation.
