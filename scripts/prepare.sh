#!/usr/bin/env sh
# The one quality gate. CI and developers run the same script.
#
#   ./scripts/prepare.sh          fix mode (default locally): clang-format in place, then every check
#   ./scripts/prepare.sh --check  check mode (default when CI=true): changes nothing
#
# clang-tidy and cppcheck run when installed. They are required in CI (and with REQUIRE_TOOLS=1).
set -eu
cd -P "$(dirname "$0")/.."

mode=fix
[ "${CI:-}" = "true" ] && mode=check
for arg in "$@"; do
    case "$arg" in
    --check) mode=check ;;
    --fix) mode=fix ;;
    *) printf '%s\n' "Usage: scripts/prepare.sh [--check|--fix]" >&2; exit 2 ;;
    esac
done
require="${REQUIRE_TOOLS:-}"
[ "${CI:-}" = "true" ] && require=1
preset="${ESSENTIAL_PRESET:-ci}"

step() {
    label=$1; shift
    printf '[gate] START %s\n' "$label"
    if "$@"; then printf '[gate] OK    %s\n' "$label"; else
        status=$?; printf '[gate] FAIL  %s (exit %s)\n' "$label" "$status" >&2; return "$status"
    fi
}

# Find a tool on PATH or in a Homebrew LLVM install.
find_tool() {
    name=$1
    if command -v "$name" >/dev/null 2>&1; then command -v "$name"; return 0; fi
    for dir in "$(brew --prefix llvm 2>/dev/null || true)/bin" /usr/lib/llvm-*/bin; do
        [ -x "$dir/$name" ] && { printf '%s\n' "$dir/$name"; return 0; }
    done
    return 1
}

optional() {
    tool=$1; label=$2; shift 2
    if path=$(find_tool "$tool"); then step "$label" "$path" "$@"
    elif [ -n "$require" ]; then printf '[gate] FAIL  %s: %s is not installed\n' "$label" "$tool" >&2; return 1
    else printf '[gate] SKIP  %s (install %s to enable)\n' "$label" "$tool"; fi
}

sources=$(find include src apps tests c -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.c' -o -name '*.h' \))
format=$(find_tool clang-format) || { printf '[gate] FAIL  clang-format is not installed\n' >&2; exit 1; }

if [ "$mode" = fix ]; then
    # shellcheck disable=SC2086
    step "format (clang-format)" "$format" -i $sources
else
    # shellcheck disable=SC2086
    step "format check (clang-format)" "$format" --dry-run -Werror $sources
fi

step "configure ($preset)" cmake --preset "$preset"
step "build, warnings as errors ($preset)" cmake --build --preset "$preset"
step "tests under sanitizers ($preset)" ctest --preset "$preset"

# shellcheck disable=SC2086
optional clang-tidy "lint (clang-tidy)" -p "build/$preset" --quiet --header-filter="^$PWD/(include|c/include|src|apps)/" $(find src apps tests c -type f \( -name '*.cpp' -o -name '*.c' \) -not -path '*/_deps/*')
optional cppcheck "static analysis (cppcheck)" --project="build/$preset/compile_commands.json" \
    --enable=warning,performance,portability --error-exitcode=1 --inline-suppr --quiet \
    -i"build/$preset/_deps" --suppress='*:*/_deps/*'
printf '[gate] all checks passed (%s mode)\n' "$mode"
