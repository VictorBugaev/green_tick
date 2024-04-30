#include "my_math.h"

long double my_floor(double x) {
  if (MY_IS_NAN(x) || MY_IS_INF(x)) return x;
  if (x < 0 && my_fmod(x, 1)) {
    x -= 1;
  }
  return (int)x;
}