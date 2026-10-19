# NoeMixerr v0.4.0

Development milestone for the LMMS-derived NoeMixerr DAW. This version number does not imply feature parity with FL Studio or a finished commercial DAW.

## Included
- Existing C++/Qt desktop DAW, inherited synths, piano roll, mixer and export workflows.
- Standalone NoeAI C++ MCP server with inspected, previewed, permission-gated project edits, including notes, batch notes, track creation, pattern creation, track renaming, tempo and mixer values.
- Standalone PortAudio input recorder to PCM WAV, using a preallocated callback ring and background disk writer.
- Project fixture audits, cross-platform build checks and headless audio render tests.

## Not yet complete
- In-editor multitrack audio recording and monitoring, overdubbing and take comping.
- Modern VST3/CLAP plugin hosting and sandboxing.
- Native NoeEngine runtime integration and in-editor AI UI.
- Installer signing, packaging and full audio interface/device testing.

## Compatibility
The LMMS codebase and original third-party licenses remain subject to their respective license terms, including GPL. Native audio recording and MCP tools are independent optional executables.

Do not call a build release-ready until Linux, Windows and macOS builds, project reopening and actual WAV rendering all pass.
