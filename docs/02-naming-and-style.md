# 2. Naming and style

- Namespace `essential`. Types `PascalCase`, functions and variables `snake_case`, private members end with `_`, constants `kPascalCase`.
- Files `snake_case.hpp` / `.cpp`; one primary type or topic per file.
- C: functions and types prefixed `essential_`, macros `ESSENTIAL_` and `SCREAMING_SNAKE`.
- Format with clang-format (`.clang-format`, Google-based, 100 columns). The gate formats in fix mode and fails in check mode.
- Includes: the matching header first, then standard headers, then project headers. Include what you use.
- Document every public function with `///`: what it does, ownership, error cases.
