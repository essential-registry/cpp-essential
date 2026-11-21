---
name: new-module
description: Add a C++ module (header, source, tests) to the library.
---

Add `include/essential/<name>.hpp` and `src/<name>.cpp`, list the source in `src/CMakeLists.txt`, add `tests/test_<name>.cpp` and list it in `tests/CMakeLists.txt`, return `std::expected` for failures, run `./scripts/prepare.sh`.
