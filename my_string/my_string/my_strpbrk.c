#include "../my_string.h"

char *my_strpbrk(const char *str1, const char *str2) {
  char *result = my_NULL;
  char *ptr = (char *)str1;
  while (*ptr && result == my_NULL) {
    for (my_size_t i = 0; i < my_strlen(str2); i++) {
      if (*ptr == str2[i]) {
        result = ptr;
        break;
      }
    }
    ptr++;
  }
  return result;
}
