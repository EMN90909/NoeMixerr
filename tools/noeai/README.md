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
- `inspect_project`: inspect tempo, notes and tracks in a legacy LMMS/NoeMixerr `.mmp` file.
- `propose_edit`: preview a `set_tempo` or `add_note` operation; writes nothing.
- `apply_edit`: commit a previously proposed operation, with atomic saves and a backup; **disabled by default**.

To allow writes set `NOEMIXERR_ALLOW_WRITES=1` **and** configure the MCP host to
request human approval for `apply_edit`. The boolean `confirm` argument is not
itself proof of human approval, and the server cannot enforce external host UX.

Project files must already exist within `NOEMIXERR_WORKSPACE`. The server accepts
only the paths you explicitly pass via a tool call, never arbitrary code or
shell commands. It does not read `.mmpz` in this preview.

This is a deliberately limited MCP starting point, not an AI music-generation
service or a claim of full LMMS editor integration. GPL attribution and license
terms continue to apply to the NoeMixerr DAW.
