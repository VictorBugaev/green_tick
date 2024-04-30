#include "../my_string.h"

my_size_t my_strcspn(const char *str1, const char *str2) {
  my_size_t result = 0;
  int break_flag = 1;
  for (my_size_t i = 0; i < my_strlen(str1) && break_flag; i++) {
    for (my_size_t j = 0; j < my_strlen(str2) && break_flag; j++) {
      if (str1[i] == str2[j]) break_flag = 0;
    }
    if (break_flag) result++;
  }
  return result;
}