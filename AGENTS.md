# C++ Essential: guide for AI agents

C++23 (and C17) CMake starter: static library + CLI + tests, CMake presets (debug, release, ASan+UBSan, TSan, coverage), clang-format, clang-tidy, cppcheck, Catch2, vcpkg manifest, one quality gate.

## Commands

```bash
cmake --preset debug && cmake --build --preset debug && ctest --preset debug
cmake --preset asan-ubsan && cmake --build --preset asan-ubsan && ctest --preset asan-ubsan
./build/debug/apps/cli/essential greet Ada
./scripts/prepare.sh                 # fix mode: clang-format -i, build, test under sanitizers, clang-tidy, cppcheck
./scripts/prepare.sh --check         # the CI gate (non-mutating)
cmake -DESSENTIAL_LANGS=CXX ...      # build only C++ (or C)
```

The gate is `./scripts/prepare.sh --check`. CI runs the same thing, so a change that passes locally passes in CI.

## Layout

```text
CMakeLists.txt CMakePresets.json vcpkg.json
cmake/            warnings.cmake, sanitizers.cmake, deps.cmake
include/essential/   public C++ headers (the API)
src/                 library implementation (target essential::essential)
apps/cli/            executable `essential`
tests/               Catch2 tests
c/                   the C17 side: include/essential_c, src, tests (target essential::c)
.clang-format .clang-tidy .clangd
docs/ scripts/prepare.sh
```

## Conventions

- C++23. Errors are values: return `std::expected<T, essential::Error>`. Exceptions are not used for expected failures; `main` catches everything so none escape.
- RAII for every resource. No raw `new`/`delete`, no owning raw pointers. Prefer value types; use `std::unique_ptr` when ownership must be unique.
- No `using namespace` in headers. Headers use `#pragma once`, include what they use, and live under `include/essential/`.
- Every public function is `[[nodiscard]]` when ignoring the result is a bug, and documented with a `///` comment (ownership, error cases).
- Warnings are errors in presets (`ESSENTIAL_WERROR`). Do not silence a warning: fix it. A `NOLINT` needs a comment saying why.
- Sanitizer builds must stay clean: `asan-ubsan` is what CI runs; `tsan` is for threaded code.
- C code (`c/`): C17, every pointer parameter documented (nullability, ownership, size), `extern "C"` guards in headers, no VLAs, bounded string functions only.
- Add a source file to the nearest `CMakeLists.txt` explicitly (no globbing). Tests sit in `tests/` (C++) and `c/tests/` (C).

## Rules (all Essential templates)

- **Git:** commits and pushes use the user's own git identity. Never set a Claude identity and never add `Co-Authored-By` or "Generated with" lines. Do not commit unless asked.
- Never read or print `.env` files or secrets. Every setting has an entry in `.env.example`.
- Conventional commits (`feat(scope): ...`). Feature branch, then pull request.
- Business numbers (limits, durations, thresholds) are configuration, never constants in code.
- If a rule is missing, stop and ask. Do not invent one.
- Run the gate before saying "done".

## Never

- Use `new`/`delete` or `malloc`/`free` in C++ code.
- Add `using namespace` to a header.
- Disable sanitizers, warnings-as-errors or clang-tidy checks to make the gate pass.
- Glob sources in CMake.
- Commit `build/` or `vcpkg_installed/`.

## Read next

- `docs/01-architecture.md`, `docs/02-naming-and-style.md`, `docs/03-errors-and-ownership.md`, `docs/04-testing.md`, `docs/05-tooling.md`, `docs/06-release.md`
