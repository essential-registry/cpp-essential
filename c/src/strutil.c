#include "essential_c/strutil.h"

#include <ctype.h>
#include <string.h>

size_t essential_trim(const char* input, char* out, size_t out_size) {
  if (input == NULL || out == NULL) {
    return 0;
  }
  while (*input != '\0' && isspace((unsigned char)*input) != 0) {
    ++input;
  }
  size_t length = strlen(input);
  while (length > 0 && isspace((unsigned char)input[length - 1]) != 0) {
    --length;
  }
  if (out_size > 0) {
    const size_t copied = length < out_size - 1 ? length : out_size - 1;
    memcpy(out, input, copied);
    out[copied] = '\0';
  }
  return length;
}
