#!/usr/bin/env python3
"""Validate standalone recorder RIFF/PCM output without requiring a microphone."""
from pathlib import Path
import subprocess
import sys
import tempfile
import wave

binary=Path(sys.argv[1]).resolve()
assert binary.is_file(), binary
with tempfile.TemporaryDirectory() as folder:
    wav=Path(folder)/"capture-test.wav"
    run=subprocess.run([str(binary),"--self-test",str(wav)],capture_output=True,text=True,timeout=30)
    assert run.returncode==0,(run.stdout,run.stderr)
    with wave.open(str(wav),"rb") as reader:
        assert reader.getnchannels()==2
        assert reader.getframerate()==48000
        assert reader.getsampwidth()==2
        assert reader.getnframes()==24000
        pcm=reader.readframes(24000)
    assert len(pcm)==96000
    assert any(byte!=0 for byte in pcm)
    duplicate=subprocess.run([str(binary),"--self-test",str(wav)],capture_output=True,text=True,timeout=30)
    assert duplicate.returncode!=0,"Recorder must never overwrite an existing take"
print("NoeMixerr native WAV recording backend synthetic tests passed")
