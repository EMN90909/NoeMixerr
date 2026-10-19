#!/usr/bin/env python3
"""Headless WAV export acceptance test using an original LMMS music project.

Unlike XML-only tests, this actually invokes the NoeMixerr synth/audio graph.
"""
from pathlib import Path
import os
import subprocess
import sys
import tempfile
import wave

ROOT = Path(__file__).resolve().parent.parent


def main():
    if len(sys.argv) != 2:
        raise SystemExit("Usage: python tools/test_audio_render.py <NoeMixerr executable>")
    binary = Path(sys.argv[1]).resolve()
    if not binary.is_file() and (binary.parent / (binary.name+".exe")).is_file():
        binary = binary.with_name(binary.name + ".exe")
    if not binary.is_file():
        raise FileNotFoundError(binary)
    project = ROOT / "data/projects/tutorials/editing_note_volumes.mmp"
    if not project.exists():
        raise FileNotFoundError(project)
    with tempfile.TemporaryDirectory(prefix="noemixerr-render-") as folder:
        output = Path(folder) / "render.wav"
        env = os.environ.copy()
        env.setdefault("QT_QPA_PLATFORM", "offscreen")
        result = subprocess.run(
            [str(binary), "render", str(project), "-f", "wav", "-o", str(output)],
            cwd=str(ROOT), env=env, capture_output=True, text=True, timeout=180
        )
        if result.returncode:
            raise AssertionError(f"DAW render failed ({result.returncode}): "
                                 f"{result.stdout[-2500:]}\n{result.stderr[-2500:]}")
        if not output.is_file():
            raise AssertionError("DAW returned success but did not write a WAV file")
        with wave.open(str(output), "rb") as audio:
            assert audio.getframerate() in (44100, 48000), audio.getframerate()
            assert audio.getnchannels() == 2
            assert audio.getnframes() > 22050
            data = audio.readframes(min(audio.getnframes(), audio.getframerate() * 20))
            assert any(v != 0 for v in data), "Export is silent"
            print(f"Rendered {audio.getnframes()} frames at {audio.getframerate()}Hz from a legacy LMMS project")


if __name__ == "__main__":
    main()
