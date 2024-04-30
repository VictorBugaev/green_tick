#include "../my_string.h"

char *my_strtok(char *str, const char *delim) {
  static char *new_str = my_NULL;
  if (str != my_NULL) {
    new_str = str;
    while (*new_str && my_strchr(delim, *new_str)) *new_str++ = '\0';
  }
  if (new_str == my_NULL) return str;

  if (*new_str != '\0') {
    str = new_str;
    while (*new_str && !my_strchr(delim, *new_str)) ++new_str;
    while (*new_str && my_strchr(delim, *new_str)) *new_str++ = '\0';
  } else
    str = my_NULL;
  return str;
}