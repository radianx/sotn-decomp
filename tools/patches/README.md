# PSY-Z fixes for the US native port

This patch modifies the upstream PSY-Z source pinned by `tools/psyz` at
`f8780dcf04c93fa4f41e2c8a838be1a8ee15b6df`. Fork modifications are dated
2026-10-26. The affected file in `psyz/src/psyz/`
remains under **MPL-2.0**; see [LICENSE.MPL-2.0](LICENSE.MPL-2.0) and the
[upstream repository](https://github.com/Xeeynamo/psyz/tree/f8780dcf04c93fa4f41e2c8a838be1a8ee15b6df).

From the sotn-decomp root, apply the audio patch once to a clean pinned submodule:

```sh
git -C tools/psyz apply ../patches/psyz-audio-stream-voices.patch
```

The patch preserves XA audio timing between filtered sectors. The pinned
upstream version already includes the Unix file-open and non-looping SPU voice
fixes. Native regression tests cover these behaviors.

The submodule remains pinned to the public upstream commit. The patches carry
the local modifications without requiring an unpublished submodule revision.
