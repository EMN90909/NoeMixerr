#!/usr/bin/env python3
"""Exercise original LMMS project loading with the NoeMixerr C++ CLI.

This is a legacy-project upgrade round-trip smoke test. It does not validate
realtime playback, plugins, UI controls, or full project fidelity.
"""
from pathlib import Path
import os
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parent.parent
LEGACY = ROOT / "data/projects/tutorials/editing_note_volumes.mmp"


def details(path):
    root = ET.parse(path).getroot()
    assert root.tag in {"lmms-project", "noemixerr-project"}, root.tag
    head = root.find("head")
    assert head is not None
    bpm = head.attrib.get("bpm")
    notes = root.findall(".//note")
    tracks = root.findall(".//track")
    assert bpm and tracks and notes, "Legacy fixture must include actual musical content"
    return int(bpm), len(notes), len(tracks), root


def main():
    if len(sys.argv) != 2:
        raise SystemExit("Usage: python tools/test_project_compatibility.py <NoeMixerr executable>")
    executable = Path(sys.argv[1]).resolve()
    if not executable.is_file() and (executable.parent / (executable.name + ".exe")).is_file():
        executable = executable.with_name(executable.name + ".exe")
    assert executable.is_file(), executable
    base_bpm, base_notes, base_tracks, _ = details(LEGACY)

    env = os.environ.copy()
    env.setdefault("QT_QPA_PLATFORM", "offscreen")
    with tempfile.TemporaryDirectory(prefix="noemixerr-legacy-") as folder:
        upgraded = Path(folder) / "upgraded.mmp"
        command = [str(executable), "upgrade", str(LEGACY), str(upgraded)]
        result = subprocess.run(command, env=env, stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT, text=True, timeout=120)
        assert result.returncode == 0, f"upgrade exited {result.returncode}: {result.stdout}"
        assert upgraded.exists() and upgraded.stat().st_size > 100, "No upgraded output"
        bpm, notes, tracks, root = details(upgraded)
        assert root.tag == "lmms-project", "Preserve LMMS-compatible project XML root"
        assert bpm == base_bpm, f"Tempo changed: {base_bpm} -> {bpm}"
        assert notes == base_notes, f"Lost notes: {base_notes} -> {notes}"
        assert tracks == base_tracks, f"Lost tracks: {base_tracks} -> {tracks}"
        # Repeat to confirm that the written project remains loadable by NoeMixerr.
        reopened = Path(folder) / "reopened.mmp"
        command = [str(executable), "upgrade", str(upgraded), str(reopened)]
        result = subprocess.run(command, env=env, stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT, text=True, timeout=120)
        assert result.returncode == 0, f"reopen failed: {result.stdout}"
        assert details(reopened)[:3] == (base_bpm, base_notes, base_tracks)
    print(f"Legacy LMMS compatibility smoke test passed: {base_tracks} tracks, {base_notes} notes at {base_bpm} BPM")


if __name__ == "__main__":
    main()
