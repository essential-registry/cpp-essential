# 4. Testing

```bash
cmake --preset debug && cmake --build --preset debug && ctest --preset debug
```

- C++ tests use [Catch2](https://github.com/catchorg/Catch2) v3 (`tests/`); `catch_discover_tests` registers each `TEST_CASE` with CTest.
- C tests in `c/tests/` use a tiny assert macro and exit non-zero on failure. Switch to cmocka or Unity when you need fixtures.
- CI runs the `ci` preset, which is `asan-ubsan`: address and undefined-behaviour sanitizers are on for every test.
- Threaded code: also run the `tsan` preset.
- Coverage: the `coverage` preset adds LLVM instrumentation; run the tests, then `llvm-profdata merge` and `llvm-cov report`.
- Catch2 comes from vcpkg when present, otherwise it is fetched with CMake `FetchContent` (see `cmake/deps.cmake`).
