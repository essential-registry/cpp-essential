# 5. Tooling

| Task | Tool | Config |
| --- | --- | --- |
| Build | CMake 3.28+ with Ninja, presets | `CMakeLists.txt`, `CMakePresets.json` |
| Dependencies | vcpkg manifest (optional) | `vcpkg.json` |
| Format | clang-format | `.clang-format` |
| Lint | clang-tidy (bugprone, cert, cppcoreguidelines, modernize, performance, readability) | `.clang-tidy`, `tests/.clang-tidy` |
| Static analysis | cppcheck | gate script |
| Sanitizers | ASan, UBSan, TSan | `cmake/sanitizers.cmake`, presets |
| Editor | clangd | `.clangd` (reads `build/debug/compile_commands.json`) |

## Presets

`debug`, `release`, `asan-ubsan`, `tsan`, `coverage`, `ci` (= asan-ubsan). Add `-vcpkg` variants (`debug-vcpkg`, `release-vcpkg`) when `VCPKG_ROOT` is set.

## The gate

`./scripts/prepare.sh` formats the sources, builds the `ci` preset with warnings as errors, runs the tests under sanitizers, then clang-tidy and cppcheck. `--check` formats nothing and is what CI runs. clang-tidy and cppcheck are skipped locally when not installed (`REQUIRE_TOOLS=1` makes that a failure); on macOS install LLVM with `brew install llvm` and the script finds it.
