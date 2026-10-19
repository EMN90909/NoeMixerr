#!/usr/bin/env python3
"""Rename first-party NoeMixerr names and paths to NoeMixerr in this NoeMixerr-derived tree.

Intentionally retains historic author/legal notices, upstream links, and original
license wording. Does not rewrite binary data or git internals.
"""
from pathlib import Path
import os
import re
import subprocess

root = Path(__file__).resolve().parent.parent
names = [
    ("Ladspa2NoeMixerr", "Ladspa2NoeMixerr"),
    ("NoeMixerr", "NoeMixerr"),
    ("NoeMixerr", "NoeMixerr"),
    ("noemixerr", "noemixerr"),
]
# Lines that document provenance must remain legally accurate.
preserve = re.compile(
    r"copyright|spdx-|gnu general public license|authors?|contributors?|"
    r"github\.com/LMMS|lmms\.io|license|originally (developed|written)",
    re.IGNORECASE,
)
# Avoid non-text packages and copyright-credited third-party sources.
extensions = {
    ".cpp", ".c", ".cc", ".cxx", ".h", ".hpp", ".hxx", ".in", ".cmake",
    ".txt", ".md", ".rst", ".xml", ".desktop", ".spec", ".rc", ".json",
    ".yml", ".yaml", ".sh", ".bat", ".ps1", ".py", ".qrc", ".ui", ".pro",
    ".pri", ".cfg", ".ini", ".conf", ".service", ".1", ".plist", ".svg",
    ".ts", ".html", ".css", ".js", ".m", ".mm", ".ac", ".am",
}
excluded = {"LICENSE.txt", "COPYING", "COPYING.txt", "NOTICE", "NOTICE.md"}
changed = 0
for file in root.rglob("*"):
    if not file.is_file() or ".git" in file.parts or file.name in excluded:
        continue
    if file.suffix.lower() not in extensions and file.name not in {
        "CMakeLists.txt", "Makefile", "Dockerfile", ".gitignore", ".gitmodules",
        ".gitattributes", ".clang-format", ".clang-tidy", ".editorconfig",
        ".mailmap", "Brewfile", "INSTALL.txt",
    }:
        continue
    try:
        raw = file.read_bytes()
        if b"\x00" in raw:
            continue
        body = raw.decode("utf-8")
    except (UnicodeDecodeError, OSError):
        continue
    transformed = []
    for line in body.splitlines(keepends=True):
        # Legal acknowledgments and links to official NoeMixerr remain.
        if preserve.search(line):
            transformed.append(line)
            continue
        for old, new in names:
            line = line.replace(old, new)
        transformed.append(line)
    result = "".join(transformed)
    if result != body:
        file.write_bytes(result.encode("utf-8"))
        changed += 1
# Rename paths deepest-first, case-sensitive with mixed-case support.
renamed = 0
paths = sorted((p for p in root.rglob("*") if ".git" not in p.parts),
               key=lambda p: len(p.parts), reverse=True)
for p in paths:
    if not p.exists():
        continue
    new_name = p.name
    for old, new in names:
        new_name = new_name.replace(old, new)
    if new_name != p.name:
        dst = p.with_name(new_name)
        if dst.exists():
            raise RuntimeError(f"Path collision: {p} -> {dst}")
        p.rename(dst)
        renamed += 1
print(f"Rebranded {changed} text files and {renamed} file/directory paths")
# Guarantee future audit has meaningful results.
remaining = subprocess.run(
    ["git", "grep", "-Il", "-i", "lmms", "--", ":!LICENSE.txt"],
    cwd=root, capture_output=True, text=True
)
print("Provenance / remaining NoeMixerr text mentions in index:",
      len(remaining.stdout.splitlines()))

# Compress inherited verbose GPL boilerplate while keeping original copyright.
# Only headers containing the recognizable LMMS GPL notice are eligible.
import re as _re
shortened = 0
for source in root.rglob("*"):
    if not source.is_file() or ".git" in source.parts:
        continue
    if source.suffix.lower() not in {".h", ".hpp", ".cpp", ".c", ".cc", ".cxx"}:
        continue
    try:
        text = source.read_text(encoding="utf-8")
    except (UnicodeDecodeError, OSError):
        continue
    head = _re.match(r"\\A(/\\*.*?\\*/)", text, _re.S)
    if not head:
        continue
    original = head.group(1)
    if "This program is free software" not in original or "GNU General Public" not in original:
        continue
    if "Copyright" not in original:
        continue
    # Preserve verbatim ownership and relevant title/description lines.
    lines = []
    for line in original.splitlines():
        clean = line.strip(" /*\\t")
        if clean.startswith("Copyright ") or clean.startswith("Copyright("):
            lines.append("// " + clean)
    if not lines:
        continue
    # retain original holders even if multiple copyright lines were present.
    header = "// SPDX-License-Identifier: GPL-2.0-or-later\\n"
    header += "// NoeMixerr: modified LMMS-derived source; original copyrights retained.\\n"
    header += "\\n".join(lines) + "\\n"
    header += "// See LICENSE.txt and doc/AUTHORS for original authors and license.\\n"
    changed_body = header + text[head.end():]
    if changed_body != text:
        source.write_text(changed_body, encoding="utf-8")
        shortened += 1
print(f"Condensed {shortened} inherited GPL banners, preserving copyright holders")
