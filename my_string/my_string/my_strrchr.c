#include "../my_string.h"

char *my_strrchr(const char *str, int c) {
  char *result = my_NULL;
  if ((c >= 0) && (str != my_NULL)) {
    for (my_size_t i = my_strlen(str) + 1; i > 0; i--) {
      if (str[i - 1] == (char)c) {
        result = (char *)(str + i - 1);
        break;
      }
    }
  }
  return result;
}
