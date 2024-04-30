#include "../my_string.h"
char *my_strcat(char *dest, const char *src) {
  my_size_t length = 0;
  while (*dest) {
    dest++;
    length++;
  }
  while (*src) {
    *dest = *src;
    dest++;
    src++;
    length++;
  }
  dest = dest - length;
  return dest;
}