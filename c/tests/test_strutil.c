/* A tiny framework-free test: exit code 0 means pass. Swap in cmocka/Unity when you need more. */
#include <stdio.h>
#include <string.h>

#include "essential_c/strutil.h"

static int failures = 0;

#define CHECK(condition)                                                                  \
  do {                                                                                    \
    if (!(condition)) {                                                                   \
      (void)fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #condition); \
      ++failures;                                                                         \
    }                                                                                     \
  } while (0)

static void trims_both_ends(void) {
  char out[16];
  CHECK(essential_trim("  hi there \n", out, sizeof out) == 8);
  CHECK(strcmp(out, "hi there") == 0);
}

static void truncates_safely(void) {
  char out[4];
  CHECK(essential_trim("abcdef", out, sizeof out) == 6);
  CHECK(strcmp(out, "abc") == 0);
}

static void handles_empty_and_null(void) {
  char out[4] = "xyz";
  CHECK(essential_trim("   ", out, sizeof out) == 0);
  CHECK(out[0] == '\0');
  CHECK(essential_trim(NULL, out, sizeof out) == 0);
}

int main(void) {
  trims_both_ends();
  truncates_safely();
  handles_empty_and_null();
  return failures == 0 ? 0 : 1;
}
