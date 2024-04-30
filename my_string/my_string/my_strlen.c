#include "../my_string.h"

my_size_t my_strlen(const char* str) {
  my_size_t length = 0;
  while (*(str + length)) {
    length++;
  }
  return length;
}