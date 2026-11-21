# C++ Essential

A CMake starter for C++23 and C17 with the essentials already set up: a library, a CLI, tests, sanitizer presets, formatting, static analysis, CI and an agent guide.

## Layout

```text
include/essential/   public C++ headers
src/                 library (essential::essential)
apps/cli/            executable `essential`
tests/               Catch2 tests
c/                   C17 library and tests (essential::c)
cmake/               warnings, sanitizers, dependencies
docs/                architecture, style, errors, testing, tooling, release
scripts/prepare.sh   the quality gate
```

## Build and run

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
./build/debug/apps/cli/essential greet Ada
```

Presets: `debug`, `release`, `asan-ubsan`, `tsan`, `coverage`, `ci`. Only need one language? Configure with `-DESSENTIAL_LANGS=CXX` or `-DESSENTIAL_LANGS=C`.

## Quality gate

```bash
./scripts/prepare.sh            # fix: clang-format, build (warnings as errors), sanitizer tests, clang-tidy, cppcheck
./scripts/prepare.sh --check    # what CI runs
```

## Dependencies

Catch2 comes from vcpkg (`vcpkg.json`, use the `*-vcpkg` presets with `VCPKG_ROOT` set) or is fetched automatically when vcpkg is not used.

## Working with AI agents

`AGENTS.md` is the guide agents follow (`CLAUDE.md` points to it). `.claude/` has permissions, a formatter hook, a reviewer agent and skills.

## License

MIT.
