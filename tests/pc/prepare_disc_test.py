# SPDX-License-Identifier: AGPL-3.0-or-later
"""Check CHD cache reuse and failure cleanup without requiring game files."""

import importlib.util
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location(
    "prepare_pc_disc", Path(__file__).resolve().parents[2] / "tools/prepare_pc_disc.py"
)
disc = importlib.util.module_from_spec(spec)
spec.loader.exec_module(disc)


class DiscPreparationTest(unittest.TestCase):
    def test_cache_and_failed_extraction(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "game.chd"
            source.write_bytes(b"test input")

            def extract(args, **kwargs):
                Path(args[args.index("-o") + 1]).write_text('FILE "disc.bin" BINARY\n')
                Path(args[args.index("-ob") + 1]).write_bytes(b"disc data")

            with patch.object(disc, "ROOT", root), patch.dict(
                disc.os.environ, {"CHDMAN": "test-chdman"}
            ), patch.object(disc.subprocess, "run", side_effect=extract) as run:
                cue = disc.prepare(source)
                self.assertTrue(cue.is_file())
                self.assertEqual(disc.prepare(source), cue)
                self.assertEqual(run.call_count, 1)
                self.assertEqual(source.read_bytes(), b"test input")
                source.write_bytes(b"different disc")
                run.side_effect = subprocess.CalledProcessError(1, "test-chdman")
                with self.assertRaises(subprocess.CalledProcessError):
                    disc.prepare(source)
                self.assertEqual(list(cue.parent.parent.iterdir()), [cue.parent])


if __name__ == "__main__":
    unittest.main()
