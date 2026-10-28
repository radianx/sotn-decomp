# Video filters

Open **F1**, select **Video filter** near the bottom, and change it with
Left/Right. The following row adjusts **Filter strength** from 0 to 100%.
Close F1 to see the result. Both settings persist in the PC settings file.
Original is the default; 0% strength also restores the original nearest path.

| Filter | Appearance | Useful for |
| --- | --- | --- |
| Original (nearest) | Sharp, unmodified pixels | Original sprite detail and comparisons |
| Bilinear | Smooth interpolation between neighboring pixels | A softer image without edge reconstruction |
| CRT (soft) | Scanlines, a light RGB grille and horizontal softness | A flat CRT-style presentation without flicker or cropped corners |
| xBR level 2 | Reconstructs diagonal edges and rounds pixel corners | A smoother, more illustrated appearance |

Start around the default 75% strength. xBR changes fine sprite and font details;
use Original if those changes are undesirable. CRT reduces scanline modulation
at small window sizes. There is no temporal flicker, barrel distortion or
chromatic separation. These are visual options, independent of reduced flashes
and palette assistance.

Filtering runs on the final game image, including its HUD, menus, widescreen
extensions and movies. The separate F1/F5 windows remain unfiltered. Resizing,
fullscreen and both aspect ratios retain their existing viewport rules.
The source crop is clamped before sampling, preventing neighboring VRAM textures
from leaking into the image. Scanlines and edge detection use the game's pixel
grid rather than the internal rendering multiplier.

Game textures, PS1 VRAM and framebuffer effects stay unchanged. Raw captures,
transition snapshots and save thumbnails remain unfiltered, so filtering cannot
accumulate in feedback effects. No extra CPU frame readback is needed to present
a filter. xBR costs more GPU work than CRT or Bilinear.

## Implementation and attribution

The xBR implementation adapts Hyllian's
[MIT-licensed xBR-lv2 shader](https://github.com/libretro/glsl-shaders/blob/master/xbr/shaders/xbr-lv2.glsl),
including its license notice. It is xBR level 2, rather than xBRZ, HQx or ScaleFX.
The CRT pass is a small static shader written for this port.

Apply the three SDK patches listed in [Native Linux](native_linux.md) in order.
Presentation shader sources, generated SPIR-V/Metal/OpenGL headers and their
rebuild script are carried by `tools/patches/psyz-video-filters.patch`.
Normal builds use the bundled headers without installing shader tools.
To regenerate or verify them, follow [the patch guide](../tools/patches/README.md).

Linux Vulkan and OpenGL are the runtime test targets. Windows D3D12 currently
falls back to nearest; Windows OpenGL and Metal still need platform testing.
Shader creation failures preserve the original presentation and log a warning.
