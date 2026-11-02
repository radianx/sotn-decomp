# SPDX-License-Identifier: AGPL-3.0-or-later
set pagination off
set confirm off
set debuginfod enabled off
break SpawnPoint_StageForName
commands
silent
set 'spawn_point.c'::s_SpawnPoints[0].stageId = 2
set 'spawn_point.c'::s_SpawnPoints[0].roomIndex = 14
set 'spawn_point.c'::s_SpawnPoints[0].x = 128
set 'spawn_point.c'::s_SpawnPoints[0].y = 128
disable 1
continue
end
python
import gdb
import subprocess
import struct
from pathlib import Path

rawFrames = {}


def upload_pattern():
    execute = lambda command: gdb.execute(command, to_string=True)
    # Keep the same source origin for pixel-exact comparisons at fractional scale.
    execute("set display_area.x = 0")
    execute("set display_area.y = 0")
    left = int(gdb.parse_and_eval("PcViewLeft()"))
    width = int(gdb.parse_and_eval("PcViewRight()")) - left
    pixels = []
    colors = (0x001F, 0x03E0, 0x7C00, 0x7C1F, 0x7FE0, 0x7FFF)
    for y in range(240):
        for x in range(width):
            color = colors[min(5, x * 6 // width)] if y < 90 else 0x1084
            if y >= 90 and abs(x - width // 2) < (y - 90):
                color = 0x7C1F if (x // 8 + y // 8) % 2 else 0
            pixels.append(color)
    payload = struct.pack("<%dH" % len(pixels), *pixels)
    execute("set $pattern = (void*)malloc(%d)" % len(payload))
    execute("set $patternRect = (RECT*)calloc(1,sizeof(RECT))")
    execute("set $patternRect->w = %d" % width)
    execute("set $patternRect->h = 240")
    gdb.selected_inferior().write_memory(int(gdb.parse_and_eval("$pattern")), payload)
    execute("set $drawEnv = (DRAWENV*)malloc(sizeof(DRAWENV))")
    execute("call GetDrawEnv($drawEnv)")
    for buffer in (0, 1):
        execute("call PutDrawEnv(&g_GpuBuffers[%d].draw)" % buffer)
        execute(
            "set $patternRect->x = g_GpuBuffers[%d].draw.clip.x + %d" % (buffer, left)
        )
        execute("set $patternRect->y = g_GpuBuffers[%d].draw.clip.y" % buffer)
        execute("call LoadImage($patternRect,(unsigned long*)$pattern)")
        execute("call DrawSync(0)")
    execute("call PutDrawEnv($drawEnv)")
    execute("call DrawSync(0)")
    execute("call free($drawEnv)")
    execute("call free($patternRect)")
    execute("call free($pattern)")


def video_step(frame):
    execute = lambda command: gdb.execute(command, to_string=True)
    if frame == 1:
        execute("call SetFullScreen(1)")
        execute("set g_GameEngineStep = Engine_0x70")
        execute("set g_PcSettings.widescreen = 1")
    if frame == 100:
        execute("set g_PcSettings.widescreen = 0")
    phases = {
        20: (0, 75),
        40: (4, 0),
        60: (4, 50),
        80: (4, 100),
        110: (0, 75),
        130: (4, 0),
        150: (4, 50),
        170: (4, 100),
    }
    if frame in phases:
        mode, strength = phases[frame]
        execute("set g_PcSettings.videoFilter = %d" % mode)
        execute("set g_PcSettings.filterStrength = %d" % strength)
    captures = {
        30: "original",
        50: "zero",
        70: "synthwave-50",
        90: "synthwave-100",
        120: "original",
        140: "zero",
        160: "synthwave-50",
        180: "synthwave-100",
    }
    if frame not in captures:
        return
    label = "wide" if frame < 100 else "original-aspect"
    name = captures[frame]
    print(
        "VIDEO_CAPTURE %s %s mode=%s strength=%s"
        % (
            label,
            name,
            gdb.parse_and_eval("Psyz_VideoGetFilter()"),
            gdb.parse_and_eval("Psyz_VideoGetFilterStrength()"),
        ),
        flush=True,
    )
    path = Path("@QA@/%s-%s.png" % (label, name))
    subprocess.run(
        ["import", "-window", "Castlevania: Symphony of the Night", str(path)],
        check=True,
    )
    execute("set $width = (int*)calloc(2,4)")
    execute("set $raw = Psyz_VideoAllocCapturedFrame($width,$width+1)")
    length = int(gdb.parse_and_eval("$width[0]*$width[1]*3"))
    address = int(gdb.parse_and_eval("$raw"))
    data = bytes(gdb.selected_inferior().read_memory(address, length))
    execute("call free($raw)")
    execute("call free($width)")
    if name == "original":
        rawFrames[label] = data
    else:
        assert rawFrames[label] == data, name + " changed raw capture"
    if name == "synthwave-100":
        print("VIDEO_SYNTHWAVE_RAW_UNCHANGED_PASS " + label, flush=True)

end
set $videoFrame = 0
break RunMainEngine if g_Timer >= 80
commands
silent
set $videoFrame = $videoFrame + 1
# Freeze gameplay and its animation clock while the normal presentation loop runs.
set g_Timer = 80
python video_step(int(gdb.parse_and_eval('$videoFrame')))
if $videoFrame == 180
printf "VIDEO_SYNTHWAVE_PASS\n"
quit
end
continue
end
break PlatformBackend_Present if $videoFrame > 5
commands
silent
python upload_pattern()
continue
end
run
