#include "../my_string.h"

void *my_memset(void *str, int c, my_size_t n) {
  unsigned char *ptr = str;
  unsigned char value = (unsigned char)c;

  for (my_size_t i = 0; i < n; ++i) {
    ptr[i] = value;
  }
  return str;
}