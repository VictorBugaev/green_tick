#include "../my_string.h"

char *my_strchr(const char *str, int c) {
  char *result = my_NULL;
  my_size_t len = my_strlen(str);
  for (my_size_t i = 0; i < len + 1; i++) {
    if (*str == (char)c) {
      result = (char *)str;
      break;
    }
    str++;
  }
  return result;
}