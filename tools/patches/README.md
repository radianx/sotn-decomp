# PSY-Z fixes for the US native port

This patch modifies the upstream PSY-Z source pinned by `tools/psyz` at
`f8780dcf04c93fa4f41e2c8a838be1a8ee15b6df`. Fork modifications are dated
2026-10-26–27. The affected file in `psyz/src/psyz/`
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

`psyz-pc-upgrades.patch` adds separate effect/CD mixer gain, a pause-aware
clock, rounded native-canvas fitting, native presentation cropping, and
synchronized fullscreen teardown. It also exposes ordered native draw-canvas
copies for widescreen background transitions in both SDL GPU and OpenGL backends.
Constant-UV palette quads check their actual texel for framebuffer dependencies,
avoiding unnecessary synchronization when only the texture page overlaps it.
The default SDL GPU path has rendering/readback checks at 1×/2×/4× resolution;
the OpenGL addition is compile-checked only.
Apply it after the XA patch:

```sh
git -C tools/psyz apply ../patches/psyz-pc-upgrades.patch
```

The modified SDK/platform implementation files remain MPL-2.0. Public header
additions declare those interfaces; upstream file licensing is preserved.
