#!/usr/bin/env python3
"""Check that NoeMixerr's displayed and packaged development versions agree.

Run from any directory: python3 tools/check_version.py [path/to/noemixerr]
The top-level CMakeLists.txt is the authoritative source for the release number.
"""
from __future__ import annotations

from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parent.parent


def cmake_version() -> str:
    cmake = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
    parts = []
    for component in ("MAJOR", "MINOR", "RELEASE"):
        match = re.search(
            rf"\bSET\(VERSION_{component}\s+[\"']?(\d+)[\"']?\s*\)",
            cmake, flags=re.IGNORECASE,
        )
        if not match:
            raise AssertionError(f"Missing VERSION_{component} in CMakeLists.txt")
        parts.append(match.group(1))
    return ".".join(parts)


def check_files(version: str) -> None:
    readme = (ROOT / "README.md").read_text(encoding="utf-8")
    assert f"**Current development version:** **v{version}**" in readme, (
        "README version does not match CMakeLists.txt"
    )
    notes = ROOT / f"RELEASE_NOTES_v{version}.md"
    assert notes.is_file(), f"Missing release notes: {notes.name}"
    assert notes.read_text(encoding="utf-8").startswith(f"# NoeMixerr v{version}\n")
    recorder = (ROOT / "tools/recorder/CMakeLists.txt").read_text(encoding="utf-8")
    assert re.search(
        rf"project\(NoeMixerrRecorder\s+VERSION\s+{re.escape(version)}\b",
        recorder, re.IGNORECASE
    ), "Recorder CMake version does not match"
    mcp = (ROOT / "tools/noeai/main.cpp").read_text(encoding="utf-8")
    assert f'{{"version","{version}"}}' in mcp, "MCP protocol version does not match"
    assert f'NoeMixerr MCP {version}' in mcp, "MCP CLI version does not match"


def check_binary(name: str, version: str) -> None:
    executable = Path(name).resolve()
    if not executable.is_file() and executable.with_suffix(".exe").is_file():
        executable = executable.with_suffix(".exe")
    if not executable.is_file():
        raise FileNotFoundError(executable)
    result = subprocess.run(
        [str(executable), "--version"],
        capture_output=True, text=True, timeout=30, check=True
    )
    expected = re.compile(rf"^NoeMixerr\s+{re.escape(version)}(?=[-+\s]|$)")
    assert expected.search(result.stdout), (
        f"Wrong CLI version (expected {version}): {result.stdout[:500]!r}"
    )


def main() -> int:
    if len(sys.argv) > 2:
        raise SystemExit("Usage: python3 tools/check_version.py [NoeMixerr executable]")
    version = cmake_version()
    check_files(version)
    if len(sys.argv) == 2:
        check_binary(sys.argv[1], version)
    print(f"NoeMixerr version consistency OK: v{version}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
