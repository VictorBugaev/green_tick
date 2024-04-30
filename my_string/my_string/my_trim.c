#include "../my_string.h"

void *my_trim(const char *src, const char *trim_chars) {
  char *result = my_NULL;
  if (src != my_NULL) {
    result = (char *)malloc(my_strlen(src) * sizeof(char) + 1);
    char *ptr = result;
    const char *start_fragment = src, *end_fragment = src + my_strlen(src),
               *tr_ch = trim_chars, *default_chars = " \t\n\v\r\f\0";
    if (!trim_chars) tr_ch = default_chars;
    if (my_strlen(tr_ch) == 0) tr_ch = default_chars;
    while (*start_fragment && my_strchr(tr_ch, *start_fragment) != my_NULL) {
      start_fragment++;
    }
    while (my_strchr(tr_ch, *end_fragment) != my_NULL &&
           end_fragment != start_fragment) {
      end_fragment--;
    }
    end_fragment++;
    while (start_fragment != end_fragment) {
      *ptr = *start_fragment;
      ptr++;
      start_fragment++;
    }
    *ptr = '\0';
  }
  return result;
}