# C++ Essential

[![CI](https://github.com/essential-registry/cpp-essential/actions/workflows/ci.yml/badge.svg)](https://github.com/essential-registry/cpp-essential/actions/workflows/ci.yml) ![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)

A CMake starter for C++23 and C17: a library, a CLI and tests, with sanitizer presets, formatting, static analysis, CI and an agent guide. Use one language or both.

Part of [Essential](https://github.com/essential-registry): starter templates with the tooling, structure, docs and AI-agent guide already in place.

## What you get

- **C++23** library, CLI and tests, plus a **C17** library with its own tests (build either or both with `-DESSENTIAL_LANGS`)
- **Errors as values** with `std::expected`; RAII and value semantics by default
- **CMake presets:** `debug`, `release`, `asan-ubsan`, `tsan`, `coverage`, `ci`; strict warnings as errors
- **clang-format**, **clang-tidy** (bugprone, cert, cppcoreguidelines, modernize, performance, readability) and **cppcheck**
- **Catch2** tests discovered by CTest; the CI preset runs them under AddressSanitizer and UBSan
- **Dependencies** through a vcpkg manifest, with an automatic fallback to CMake `FetchContent`
- Installable CMake package (`essential::essential`), **GitHub Actions** on Linux and macOS
- **Docs and AGENTS.md** for people and coding agents

## Requirements

- [CMake](https://cmake.org) 3.28 or newer and [Ninja](https://ninja-build.org)
- A C++23 compiler: GCC 13 or newer, or a recent Clang (developed with Apple clang 21). `std::expected` and `std::format` are required; `std::print` is not.
- `clang-format` (required by the gate); `clang-tidy` and `cppcheck` recommended (skipped locally when missing, required in CI)
- Optional: [vcpkg](https://vcpkg.io) (`VCPKG_ROOT`) for dependencies

## Quick start

Click **Use this template** on GitHub (or run `gh repo create my-project --template essential-registry/cpp-essential`), then:

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
./build/debug/apps/cli/essential greet Ada
```

Only need one language? Configure with `-DESSENTIAL_LANGS=CXX` or `-DESSENTIAL_LANGS=C` and delete the folders you do not use.

## Commands

| Command | What it does |
| --- | --- |
| `cmake --preset <name>` | Configure (`debug`, `release`, `asan-ubsan`, `tsan`, `coverage`, `ci`) |
| `cmake --build --preset <name>` | Build |
| `ctest --preset <name>` | Run the tests |
| `./scripts/prepare.sh` | Fix mode: clang-format in place, build, sanitizer tests, clang-tidy, cppcheck |
| `./scripts/prepare.sh --check` | The non-mutating gate CI runs |

## Project structure

```text
include/essential/   public C++ headers
src/                 library (essential::essential)
apps/cli/            the `essential` executable
tests/               Catch2 tests
c/                   C17 library and tests (essential::c)
cmake/               warnings, sanitizers, test dependency
docs/                architecture, style, errors, testing, tooling, release
scripts/prepare.sh   the quality gate
CMakeLists.txt  CMakePresets.json  vcpkg.json  .clang-format  .clang-tidy
```

## Architecture

The CLI depends on the library, the library exposes its API only through `include/essential/`, and the C side is a separate, independently tested target. Errors are returned as `std::expected<T, essential::Error>`; nothing owns memory through a raw pointer.

Full details: [`docs/01-architecture.md`](docs/01-architecture.md).

## Documentation

- [`docs/01-architecture.md`](docs/01-architecture.md): layers, folders and how the pieces fit
- [`docs/02-naming-and-style.md`](docs/02-naming-and-style.md): naming and code style
- [`docs/03-errors-and-ownership.md`](docs/03-errors-and-ownership.md): errors as values and ownership rules
- [`docs/04-testing.md`](docs/04-testing.md): how to test and what the gate checks
- [`docs/05-tooling.md`](docs/05-tooling.md): tools, presets and the quality gate
- [`docs/06-release.md`](docs/06-release.md): versioning and releasing

## Quality gate and CI

`./scripts/prepare.sh --check` checks formatting, builds the `ci` preset with warnings as errors, runs the tests under ASan and UBSan, then clang-tidy and cppcheck. GitHub Actions runs it on Ubuntu and macOS for every push and pull request.

## Working with AI agents

[`AGENTS.md`](AGENTS.md) is the guide coding agents follow: commands, layout, conventions and a "never" list (`CLAUDE.md` points to it). `.claude/` adds safe permissions, a formatter hook, a read-only reviewer agent and task skills. Commits always use your own git identity; the guide tells agents not to add attribution lines and not to commit unless asked.

## Make it yours

1. Rename the project, namespace and targets (`essential`).
2. Replace the example modules; add sources to the nearest `CMakeLists.txt` (no globbing).
3. Add dependencies to `vcpkg.json` and use the `*-vcpkg` presets with `VCPKG_ROOT` set.
4. Keep one language if you do not need both (see above).

## Author

Built and maintained by [Vaibhav Gosavi](https://vgseven.com). Part of [Essential](https://github.com/essential-registry).

## License

MIT. See [LICENSE](LICENSE). Copyright (c) 2025-2026 Vaibhav Gosavi (https://vgseven.com).
