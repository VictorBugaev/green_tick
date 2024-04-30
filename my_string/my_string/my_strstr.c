#include "../my_string.h"

char *my_strstr(const char *haystack, const char *needle) {
  if (haystack == my_NULL || needle == my_NULL) return my_NULL;
  if (my_strlen(needle) == 0) return (char *)haystack;

  char *result = my_NULL;
  my_size_t cmp_symb = 0;
  my_size_t pos_first = 0;

  for (my_size_t i = 0; i < my_strlen(haystack); i++) {
    if (haystack[i] == needle[cmp_symb]) {
      if (cmp_symb == 0) {
        pos_first = i;
      }
      cmp_symb++;
      if (cmp_symb == my_strlen(needle)) {
        result = (char *)(haystack + pos_first);
        break;
      }
    } else
      cmp_symb = 0;
  }
  return result;
}
