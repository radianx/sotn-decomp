# PSY-Z fixes for the US native port

These patches modify the upstream PSY-Z source pinned by `tools/psyz` at
`b52003e55c0d1b20719e984dd19bd4d760eeb14a`. Fork modifications are dated
2026-10-26. The affected files in `psyz/src/platform/` and `psyz/src/psyz/`
remain under **MPL-2.0**; see [LICENSE.MPL-2.0](LICENSE.MPL-2.0) and the
[upstream repository](https://github.com/Xeeynamo/psyz/tree/b52003e55c0d1b20719e984dd19bd4d760eeb14a).

From the sotn-decomp root, apply both once to a clean pinned submodule:

```sh
git -C tools/psyz apply ../patches/psyz-unix-open-flags.patch
git -C tools/psyz apply ../patches/psyz-audio-stream-voices.patch
```

The first patch corrects Unix file-open flags used by save files. The second
preserves XA audio timing between filtered sectors and releases completed
non-looping SPU voices. Native regression tests cover these behaviors.

The submodule remains pinned to the public upstream commit. The patches carry
the local modifications without requiring an unpublished submodule revision.
