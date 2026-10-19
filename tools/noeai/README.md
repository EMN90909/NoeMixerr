# NoeAI MCP preview (C++)

This is an optional **local stdio MCP server** for NoeMixerr project files.
It does not modify the LMMS/NoeMixerr playback engine, access AI providers,
or install a background network listener.

Build with Qt 5 or 6 Core+Xml development packages:

```sh
cmake -S tools/noeai -B build-mcp
cmake --build build-mcp --parallel
ctest --test-dir build-mcp --output-on-failure
```

Launch from an MCP-capable host:

```sh
NOEMIXERR_WORKSPACE=/absolute/path/to/projects ./build-mcp/noemixerr-mcp
```

Tools:
- `inspect_project`: inspect tempo, notes, instrument configuration and top-level tracks in a legacy LMMS/NoeMixerr `.mmp` file.
- `propose_edit`: preview `set_tempo`, `add_note`, `add_notes` (up to 256 notes), `create_instrument_track`, `create_pattern` or `set_track_mix`; writes nothing. Track duplication uses the configured instrument from an existing top-level instrument track as a template.
- `apply_edit`: commit a previously proposed operation, with atomic saves and a backup; **disabled by default**.

To allow writes set `NOEMIXERR_ALLOW_WRITES=1` **and** configure the MCP host to
request human approval for `apply_edit`. The boolean `confirm` argument is not
itself proof of human approval, and the server cannot enforce external host UX.

Project files must already exist within `NOEMIXERR_WORKSPACE`. The server accepts
only the paths you explicitly pass via a tool call, never arbitrary code or
shell commands. It does not read `.mmpz` in this preview.

Keep the DAW closed while editing the same project externally, so unsaved in-editor data does not conflict with file edits. Project changes on disk between preview and application invalidate the proposal. An edit produces a new recovery backup.

This is a deliberately limited MCP starting point, not an AI music-generation
service or a claim of full LMMS editor integration. GPL attribution and license
terms continue to apply to the NoeMixerr DAW.
