#include "../my_string.h"

void *my_to_upper(const char *str) {
  char *result = my_NULL;
  if (str) {
    result = (char *)malloc((my_strlen(str) + 1) * sizeof(char));
    my_strncpy(result, str, my_strlen(str) + 1);
  }
  if (result) {
    char *ptr = result;
    while (*ptr) {
      if (*ptr >= 'a' && *ptr <= 'z') *ptr = *ptr - 32;
      ptr++;
    }
  }
  return (char *)result;
}