#include "../my_string.h"
// c# Exceptions

// ArgumentNullException
// value is null.

// ArgumentOutOfRangeException
// startIndex is negative or greater than the length of this instance.

void *my_insert(const char *src, const char *str, my_size_t start_index) {
  char *result = my_NULL;
  if (str != my_NULL && src != my_NULL) {
    if (start_index <= my_strlen(src)) {
      my_size_t comb_len = my_strlen(src) + my_strlen(str), counter = 0;
      result = (char *)malloc((comb_len) + sizeof(char) + 1);
      char *ptr = result;
      while (counter < start_index) {
        *ptr = *src;
        ptr++;
        src++;
        counter++;
      }
      while (*str) {
        *ptr = *str;
        ptr++;
        str++;
      }
      while (*src) {
        *ptr = *src;
        ptr++;
        src++;
      }
      *ptr = '\0';
    }
  }
  return (char *)result;
}
