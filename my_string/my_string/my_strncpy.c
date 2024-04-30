#include "../my_string.h"

char *my_strncpy(char *dest, const char *src, my_size_t n) {
  my_size_t src_len = my_strlen(src);
  for (my_size_t i = 0; i < n; i++) {
    if (i <= src_len) {
      dest[i] = src[i];
    } else {
      dest[i] = 0;
    }
  }
  return dest;
}