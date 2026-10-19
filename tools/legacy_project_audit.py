#!/usr/bin/env python3
"""Offline audit of inherited LMMS project fixtures, including qCompress .mmpz.

This does not replace opening and rendering projects in the DAW. It establishes
that bundled projects remain structurally intact during source migrations.
"""
from pathlib import Path
import struct
import sys
import xml.etree.ElementTree as ET
import zlib

ROOT = Path(__file__).resolve().parent.parent
PROJECT_ROOT = ROOT / "data" / "projects"
MAX_PROJECT_BYTES = 64 * 1024 * 1024


def read_project(path: Path) -> bytes:
    data = path.read_bytes()
    if path.suffix == ".mmpz":
        if len(data) < 8:
            raise ValueError("Missing qCompress header")
        size = struct.unpack(">I", data[:4])[0]
        if not 0 < size <= MAX_PROJECT_BYTES:
            raise ValueError(f"Unexpected uncompressed size {size}")
        inflater = zlib.decompressobj()
        xml = inflater.decompress(data[4:], MAX_PROJECT_BYTES + 1)
        xml += inflater.flush(MAX_PROJECT_BYTES + 1 - len(xml))
        if len(xml) != size or not inflater.eof:
            raise ValueError("Truncated/compressed project size mismatch")
        return xml
    if len(data) > MAX_PROJECT_BYTES:
        raise ValueError("Oversize plain project")
    return data


def main() -> int:
    files = sorted(p for p in PROJECT_ROOT.rglob("*") if p.suffix in (".mmp", ".mmpz"))
    files.append(ROOT / "tests" / "emptyproject.mmp")
    if len(files) < 25:
        raise AssertionError("Unexpectedly few inherited project fixtures")
    failures = []
    total_notes = 0
    kinds = {}
    for path in files:
        try:
            root = ET.fromstring(read_project(path))
            if root.tag not in ("lmms-project", "noemixerr-project", "multimedia-project"):
                raise ValueError(f"Unrecognized legacy project root: {root.tag}")
            if root.find("head") is None:
                raise ValueError("Missing head")
            if root.find("song") is None:
                raise ValueError("Missing song")
            note_count = len(root.findall(".//note"))
            total_notes += note_count
            kinds[root.tag] = kinds.get(root.tag, 0) + 1
        except Exception as exc:
            failures.append(f"{path.relative_to(ROOT)}: {exc}")
    print(f"Parsed {len(files)-len(failures)}/{len(files)} legacy LMMS projects: "
          f"{total_notes} notes; roots={kinds}")
    for failure in failures:
        print(f"ERROR {failure}", file=sys.stderr)
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
