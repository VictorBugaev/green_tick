#include "../my_string.h"

void *my_memcpy(void *dest, const void *src, my_size_t n) {
  char *destPtr = dest;
  char *srcPtr = (char *)src;
  for (my_size_t i = 0; i < n; i++) {
    destPtr[i] = srcPtr[i];
  }
  return dest;
}