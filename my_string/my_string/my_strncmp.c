#include "../my_string.h"

int my_strncmp(const char *str1, const char *str2, my_size_t n) {
  my_size_t result = 0, counter = 0;
  while (counter < n) {
    if ((*str1 != *str2) || !*str1) {
      result = *str1 - *str2;
      break;
    }
    str1++;
    str2++;
    counter++;
  }
  return result;
}