#include "../my_string.h"

void *my_memchr(const void *str, int c, my_size_t n) {
  const char *ptr = str;
  int occurrence = 0;
  if (ptr != my_NULL) {
    for (my_size_t i = 0; i < n; i++) {
      if (ptr[i] == c && c != '\0') {
        ptr += i;
        occurrence = 1;
        break;
      }
    }
    if (!occurrence) {
      ptr = my_NULL;
    }
  }
  return (void *)ptr;
}