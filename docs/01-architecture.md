# 1. Architecture

```text
apps/cli  ->  src (essential::essential)  ->  include/essential
c/ (essential::c)   standalone C17 library with its own tests
```

| Folder | Role |
| --- | --- |
| `include/essential/` | Public C++ headers: the API. Keep them small and self-contained. |
| `src/` | Library implementation, built as the static target `essential::essential`. |
| `apps/cli/` | A thin executable that uses the library. Logic belongs in `src/`, not here. |
| `tests/` | Catch2 tests; one `test_<module>.cpp` per module. |
| `c/` | The C17 side: `include/essential_c`, `src`, `tests`. C++ can use it through its `extern "C"` header. |
| `cmake/` | Reusable CMake modules (warnings, sanitizers, test dependency). |

## One language or both

The default builds C and C++. To keep one language, configure with `-DESSENTIAL_LANGS=CXX` or `-DESSENTIAL_LANGS=C`, then delete the folders you do not need (`c/` or `src`, `apps`, `tests`, `include`).

## Targets

Link against namespaced targets (`essential::essential`, `essential::c`). The library is installable with `cmake --install`, exporting `essential::essential` for other CMake projects.
