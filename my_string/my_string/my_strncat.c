#include "../my_string.h"

char *my_strncat(char *dest, const char *src, my_size_t n) {
  char *ptr = dest + my_strlen(dest);
  for (my_size_t i = 0; i < n; i++) {
    *ptr = *src;
    ptr++;
    src++;
  }
  *ptr = '\0';
  return dest;
}