#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Exercise native menus against a local disc, with isolated configuration/saves."""

import argparse
import os
from pathlib import Path
import subprocess
import tempfile


def main():
    repo = Path(__file__).resolve().parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--binary", type=Path, default=repo / "build/local-pc/native/sotn"
    )
    parser.add_argument("--disk", type=Path, default=repo / "disks/sotn.us.cue")
    parser.add_argument(
        "--only",
        choices=(
            "pause",
            "prologue",
            "title",
            "saves",
            "inventory",
            "effects",
            "video",
        ),
    )
    args = parser.parse_args()
    binary, disk = args.binary.resolve(), args.disk.resolve()
    output = Path(tempfile.mkdtemp(prefix="pc-menu-smoke-", dir=repo / "build"))
    cases = [
        ("video", "alu"),
        ("effects", "alu"),
        ("prologue", "ric"),
        ("pause", "alu"),
        ("pause", "ric"),
        ("title", "alu"),
        ("saves", "alu"),
        ("inventory", "alu"),
        ("inventory", "ric"),
    ]
    for mode, player in cases:
        if args.only and mode != args.only:
            continue
        directory = output / f"{mode}-{player}"
        directory.mkdir()
        (directory / "disks").symlink_to(repo / "disks", target_is_directory=True)
        script = (repo / "tools/pc_menu" / f"{mode}.gdb").read_text()
        script = script.replace("@QA@", str(directory))
        commands = directory / "commands.gdb"
        commands.write_text(script)
        env = dict(os.environ, SDL_AUDIODRIVER="dummy")
        command = [
            "gdb",
            "-q",
            "-batch",
            "-x",
            str(commands),
            "--args",
            str(binary),
            "--disk",
            str(disk),
            "--player",
            player,
            "--spawn-point",
            "prologue-dracula-dialogue",
            "--config",
            str(directory / "settings.ini"),
        ]
        try:
            result = subprocess.run(
                command,
                cwd=repo,
                env=env,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                timeout=120,
            )
        except subprocess.TimeoutExpired as error:
            output = error.stdout or b""
            if isinstance(output, bytes):
                output = output.decode(errors="replace")
            (directory / "run.log").write_text(output)
            raise SystemExit(f"TIMEOUT {mode}/{player}; see {directory}/run.log")
        (directory / "run.log").write_text(result.stdout)
        if mode == "pause":
            required = [
                "MENU_SAME_WINDOW_PASS",
                "MENU_PAUSE_PASS",
                "MENU_SYSTEM_PASS",
                "MENU_FULLSCREEN_ROUNDTRIP_PASS",
                "GAMEPLAY_CTRL_ENTER_FULLSCREEN_PASS",
                "MENU_CTRL_ENTER_FULLSCREEN_PASS",
                "MENU_SHORTCUT_EVENT_CONSUMED_PASS",
                "MENU_AUDIO_DIAGNOSTICS_PASS",
                "MENU_VIRTUAL_CONTROLLER_SETTINGS_AND_ADVENTURE_PASS",
                "MENU_RAW_CAPTURE_UNCHANGED_PASS",
                "MENU_GAMEPLAY_RESUMED_PASS",
                "MENU_ACCEPT_BUTTON_DOES_NOT_LEAK_PASS",
                (
                    "MENU_ORIGINAL_CHARACTER_TRANSITION_PASS"
                    if player == "alu"
                    else "MENU_RICHTER_CHARACTER_GUARD_PASS"
                ),
            ]
        elif mode == "video":
            required = [
                "VIDEO_SYNTHWAVE_PASS",
                "VIDEO_SYNTHWAVE_RAW_UNCHANGED_PASS wide",
                "VIDEO_SYNTHWAVE_RAW_UNCHANGED_PASS original-aspect",
            ]
        elif mode == "effects":
            required = [
                "EFFECTS_GAME_STATE_VRAM_RNG_GTE_UNCHANGED_PASS",
                "LIVE_FIRE_SHIELD_GUARD_AND_SPELL_PASS",
            ]
        elif mode == "prologue":
            required = [
                "PROLOGUE_ORIGINAL_PAUSE_PASS",
                "PROLOGUE_PAUSED_PLAYER_UNCHANGED_PASS",
                "PROLOGUE_RESUME_PASS",
            ]
        elif mode == "inventory":
            required = ["INVENTORY_STATE_UNCHANGED_PASS", "INVENTORY_PREVIEW_PASS"]
            if player == "alu":
                required.extend(
                    [
                        "INVENTORY_ANIMATIONS_PASS",
                        "INVENTORY_EQUIPPED_WEAPON_PASS",
                        "INVENTORY_SHIELD_VISIBILITY_PASS",
                    ]
                )
                required.extend(
                    "INVENTORY_STATE_UNCHANGED_PASS familiar=%d" % i for i in range(8)
                )
        elif mode == "title":
            required = [
                "NATIVE_TITLE_RUNNING_PASS",
                "TITLE_MUSIC_NONZERO_PASS",
                "TITLE_SCROLL_LAST_ITEM_PASS",
                "TITLE_CHILD_MUSIC_NOT_PAUSED_PASS",
                "TITLE_RETURNS_TO_ORIGINAL_MENU_PASS",
            ]
        else:
            required = [
                "NATIVE_DECLINED_SAVE_DID_NOT_WRITE_PASS",
                "NATIVE_CONFIRMED_SAVE_WRITES_ONCE_PASS",
                "NATIVE_SAVE_ROOM_PASS",
                "NATIVE_TITLE_MENU_PASS",
                "NATIVE_LOAD_BROWSER_PASS",
                "NATIVE_TITLE_LOAD_GAMEPLAY_PASS",
                "NATIVE_RENAME_ORIGINAL_NAME_GRID_PASS",
                "NATIVE_NEW_GAME_ORIGINAL_NAME_GRID_PASS",
            ]
        missing = [marker for marker in required if marker not in result.stdout]
        if result.returncode or missing:
            raise SystemExit(
                f"FAIL {mode}/{player}: missing={missing}; see {directory}/run.log"
            )
        if mode == "video":
            for aspect in ("wide", "original-aspect"):
                original = str(directory / f"{aspect}-original.png")
                errors = []
                for name in ("zero", "synthwave-50", "synthwave-100"):
                    comparison = subprocess.run(
                        [
                            "compare",
                            "-metric",
                            "MAE",
                            original,
                            str(directory / f"{aspect}-{name}.png"),
                            "null:",
                        ],
                        text=True,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                    )
                    if comparison.returncode not in (0, 1):
                        raise SystemExit(comparison.stderr)
                    errors.append(float(comparison.stderr.split()[0]))
                if not (errors[0] == 0 and 0 < errors[1] < errors[2]):
                    raise SystemExit(f"Unexpected filter strengths: {errors}")
        print(f"PASS {mode}/{player}")
    print(f"Evidence and isolated save files: {output}")


if __name__ == "__main__":
    main()
