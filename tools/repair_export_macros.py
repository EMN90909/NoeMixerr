#!/usr/bin/env python3
"""Correct export symbols introduced by automatic LMMS-to-NoeMixerr rename.

CMake GenerateExportHeader(BASE_NAME noemixerr) defines NOEMIXERR_EXPORT,
NOEMIXERR_NO_EXPORT and NOEMIXERR_STATIC_DEFINE; the earlier mixed-case
substitutions weren't valid generated names. This is a targeted fix.
"""
from pathlib import Path
import subprocess

root = Path(__file__).resolve().parent.parent
tracked = subprocess.check_output(["git", "ls-files", "-z"], cwd=root).split(b"\0")
mapping = {
    "NOEMIXERR_EXPORT": "NOEMIXERR_EXPORT",
    "NOEMIXERR_NO_EXPORT": "NOEMIXERR_NO_EXPORT",
    "NOEMIXERR_DEPRECATED": "NOEMIXERR_DEPRECATED",
    "NOEMIXERR_STATIC_DEFINE": "NOEMIXERR_STATIC_DEFINE",
}
count = 0
for raw in tracked:
    if not raw:
        continue
    file = root / raw.decode("utf-8")
    if not file.is_file() or ".github/workflows" in file.as_posix():
        continue
    try:
        data = file.read_bytes()
        if b"\0" in data:
            continue
        text = data.decode("utf-8")
    except (OSError, UnicodeDecodeError):
        continue
    fixed = text
    for before, after in mapping.items():
        fixed = fixed.replace(before, after)
    if fixed != text:
        file.write_text(fixed, encoding="utf-8")
        count += 1
print(f"Fixed {count} source and build files with wrong generated export macros")
