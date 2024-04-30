#include "my_math.h"

int my_abs(int x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}