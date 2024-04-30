#include "my_math.h"

long double my_ceil(double x) {
  int int_part = (int)x;
  int_part += (x > 0 && (x - int_part));
  long double res = int_part;
  if (res == 0 && x < 0) res = -res;
  if (MY_IS_NAN(x) || MY_IS_INF(x)) res = x;
  return res;
}
