# 6. Release

- Update `VERSION` in `project(...)` in `CMakeLists.txt` and `CHANGELOG.md`.
- Run `./scripts/prepare.sh --check`, then the `release` preset build and tests.
- Tag `vX.Y.Z`. Consumers use the installed CMake package: `find_package(essential CONFIG)` then link `essential::essential`.
- Package with `cmake --install build/release --prefix <dir>` or `cpack`.
