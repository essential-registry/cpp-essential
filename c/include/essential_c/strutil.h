#ifndef ESSENTIAL_C_STRUTIL_H
#define ESSENTIAL_C_STRUTIL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Copy `input` into `out` without leading or trailing whitespace.
 *
 * `out` is always NUL-terminated when `out_size > 0`. Returns the length of the trimmed
 * text, which may exceed `out_size - 1`; the copy is then truncated (like snprintf).
 * `input` and `out` must not overlap. Returns 0 if either pointer is NULL.
 */
size_t essential_trim(const char* input, char* out, size_t out_size);

#ifdef __cplusplus
}
#endif

#endif /* ESSENTIAL_C_STRUTIL_H */
