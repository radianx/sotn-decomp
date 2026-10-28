# Repository Guidelines

## Project Structure & Module Organization

- `src/` contains game C code: `dra/` (engine), `st/` (stages), `boss/`, `weapon/`, and platform-specific directories such as `saturn/` and `pc/`.
- `include/` holds shared headers; `config/` holds Splat layouts, symbols, asset manifests, and reference checksums.
- `tools/` contains Python, Go, and Rust utilities with colocated tests. `docs/` documents style and terminology.
- `disks/` holds local game copies; `assets/`, `asm/`, and `build/<version>/` contain generated files. Keep these out of commits.

## Build, Test, and Development Commands

Follow the setup instructions linked from `README.md`; provide your own game copy in `disks/`.

- `make build VERSION=us`: build and verify the US binaries. Other targets include `hd`, `pspeu`, and `saturn`.
- `make`: build `us`, `hd`, and `pspeu` together.
- `make extract VERSION=us`: extract assets from prepared game files.
- `./sotn.sh check us`: verify existing build checksums.
- `make format`: apply clang-format, Black, the project C linter, and symbol/license cleanup; review the resulting diff.

For PC build setup and demo execution, follow `.github/workflows/picci.yaml`.

## Coding Style & Naming Conventions

Follow `docs/STYLE.md`, `docs/NAMING.md`, and `.clang-format`: four spaces, 80 columns, attached braces, and pointers beside types (`s32* value`). Use project types from `types.h`.

Use `PascalCase` functions/types, `camelCase` locals/members, `g_PascalCase` globals, `s_PascalCase` statics, `SCREAMING_SNAKE_CASE` macros, and `snake_case` filenames. Preserve assembly function order and binary matching; leave uncertain symbols unnamed.

## Testing Guidelines

Binary matching is the primary regression gate. Rebuild every affected version with checksum checking enabled; no numeric coverage threshold is documented.

- `make test`: Python `unittest` symbol tests (`*_test.py`).
- `go test ./tools/sotn-assets/...`: Go asset-tool tests (`*_test.go`, using Testify).
- `cargo test --manifest-path tools/lints/sotn-lint/Cargo.toml`: Rust linter tests; use the affected tool's manifest for other crates.

Add focused regression tests for tooling changes. Some integration tests require extracted game files.

## Commit & Pull Request Guidelines

History uses concise, descriptive subjects, often naming an overlay, such as `BO5: merge US and PSP`; Conventional Commit prefixes are not required.

Follow `CONTRIBUTING.md`: first-time contributors must give a heads-up before opening a PR. Explain changes, link relevant issues, and report validation. Contributors must author commit messages and submit PRs themselves; agent-assisted changes must be understood and manually operable. Spelling-only PRs are not accepted.

## Agent-Specific Instructions

When interacting with Cloudflare, use the `cf` CLI unless the project has a Wrangler configuration file.
