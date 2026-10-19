#!/usr/bin/env python3
"""Black-box local MCP protocol, authorization and atomic-save checks."""
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET

def rpc(binary, work, enabled, messages):
    env = dict(os.environ, NOEMIXERR_WORKSPACE=str(work), NOEMIXERR_ALLOW_WRITES=str(int(enabled)))
    proc = subprocess.Popen([str(binary)], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE, text=True, env=env)
    assert proc.stdin and proc.stdout
    answers = []
    for i, (name, args) in enumerate(messages, 1):
        payload = {"jsonrpc": "2.0", "id": i, "method": name}
        if args is not None:
            payload["params"] = args
        proc.stdin.write(json.dumps(payload) + "\n")
        proc.stdin.flush()
        reply = proc.stdout.readline()
        assert reply, f"Server unexpectedly stopped: {proc.poll()}"
        answers.append(json.loads(reply))
    proc.stdin.close()
    assert proc.wait(timeout=5) == 0, proc.stderr.read()
    return answers

def detail(response):
    result = response.get("result", {})
    assert not result.get("isError"), result
    return json.loads(result["content"][0]["text"])

def interactive_test(binary, root, enabled):
    env = dict(os.environ, NOEMIXERR_WORKSPACE=str(root), NOEMIXERR_ALLOW_WRITES="1" if enabled else "0")
    proc = subprocess.Popen([str(binary)], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE, text=True, env=env)
    def ask(method, args=None):
        payload = {"jsonrpc":"2.0","id":1,"method":method}
        if args is not None: payload["params"] = args
        proc.stdin.write(json.dumps(payload)+"\n")
        proc.stdin.flush()
        return json.loads(proc.stdout.readline())
    try:
        assert ask("initialize")["result"]["serverInfo"]["name"] == "noemixerr-mcp"
        assert len(ask("tools/list")["result"]["tools"]) == 3
        assert detail(ask("tools/call",{"name":"inspect_project","arguments":{"path":"test.mmp"}}))["bpm"] == 120
        bad = ask("tools/call",{"name":"inspect_project","arguments":{"path":"../test.mmp"}})
        assert bad["result"]["isError"]
        plan = detail(ask("tools/call",{"name":"propose_edit","arguments":{
            "path":"test.mmp","operation":"set_tempo","bpm":130
        }}))["plan_id"]
        assert ET.parse(root/"test.mmp").getroot().find("head").get("bpm") == "120"
        refused = ask("tools/call",{"name":"apply_edit","arguments":{"plan_id":plan,"confirm":False}})
        assert refused["result"]["isError"]
        trial = ask("tools/call",{"name":"apply_edit","arguments":{"plan_id":plan,"confirm":True}})
        if not enabled:
            assert trial["result"]["isError"]
            return
        assert detail(trial)["applied"]
        assert ET.parse(root/"test.mmp").getroot().find("head").get("bpm") == "130"
        assert len(list(root.glob("*.bak"))) == 1
        plan = detail(ask("tools/call",{"name":"propose_edit","arguments":{
            "path":"test.mmp","operation":"add_note","key":66,"position":192,"length":48
        }}))["plan_id"]
        assert detail(ask("tools/call",{"name":"apply_edit","arguments":{"plan_id":plan,"confirm":True}}))["applied"]
        notes = ET.parse(root/"test.mmp").getroot().findall(".//note")
        assert len(notes)==2 and notes[-1].get("key")=="66"

        def edit(operation, **kwargs):
            params = {"path": "test.mmp", "operation": operation, **kwargs}
            proposal = detail(ask("tools/call", {"name": "propose_edit", "arguments": params}))
            assert proposal["preview_only"]
            accepted = detail(ask("tools/call", {"name": "apply_edit", "arguments": {
                "plan_id": proposal["plan_id"], "confirm": True
            }}))
            assert accepted["applied"]

        # Duplicate a working instrument configuration, with empty notes.
        edit("create_instrument_track", track_index=0, name="NoeAI Lead")
        info = detail(ask("tools/call", {"name": "inspect_project", "arguments": {"path": "test.mmp"}}))
        assert len(info["tracks"]) == 2, info
        assert info["tracks"][1]["name"] == "NoeAI Lead"
        assert info["tracks"][1]["notes"] == 0

        edit("create_pattern", track_index=1, name="Break", position=192)
        edit("add_note", pattern_index=2, key=72, position=0, length=24)
        edit("set_track_mix", track_index=1, volume=70, pan=-20, mute=True)
        edit("add_notes", notes=[
            {"pattern_index": 2, "key": 36, "position": 48, "length": 24},
            {"pattern_index": 2, "key": 38, "position": 96, "length": 24}
        ])
        xmlroot = ET.parse(root/"test.mmp").getroot()
        tracks = xmlroot.findall("./song/trackcontainer/track")
        assert len(tracks) == 2
        assert tracks[1].get("muted") == "1"
        assert tracks[1].find("instrumenttrack").get("vol") == "70"
        assert tracks[1].find("instrumenttrack").get("pan") == "-20"
        assert len(tracks[1].findall("pattern")) == 2
        assert [n.get("key") for n in tracks[1].findall("pattern")[1].findall("note")] == ["72", "36", "38"]

        invalid = ask("tools/call", {"name": "propose_edit", "arguments": {
            "path": "test.mmp", "operation": "set_track_mix",
            "track_index": 99, "volume": 80, "pan": 0, "mute": False
        }})
        assert invalid["result"]["isError"]
    finally:
        proc.stdin.close()
        assert proc.wait(timeout=5)==0,proc.stderr.read()

def main():
    binary = Path(sys.argv[1]).resolve()
    assert binary.is_file(), binary
    with tempfile.TemporaryDirectory() as temp:
        root = Path(temp)
        project = root/"test.mmp"
        xml = '<lmms-project type="song" version="1.0"><head bpm="120"/><song><trackcontainer><track type="0" name="Base"><instrumenttrack vol="100" pan="0"><instrument name="tripleoscillator"/></instrumenttrack><pattern><note key="60" pos="0" len="48"/></pattern></track></trackcontainer></song></lmms-project>'
        project.write_text(xml,encoding="utf-8")
        interactive_test(binary,root,False)
        interactive_test(binary,root,True)
    print("NoeAI MCP protocol, scope and atomic-write tests passed")

if __name__=="__main__":
    main()
