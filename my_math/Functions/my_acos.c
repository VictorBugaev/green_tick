#include "my_math.h"

long double my_acos(double x) {
  long double res = MY_NAN;
  if (x < 1 && x >= 0) res = my_atan(sqrt(1 - x * x) / x);
  if (x < 0 && x > -1) res = MY_PI + my_atan(sqrt(1 - x * x) / x);
  if (x == 1) res = 0;
  if (x == -1) res = MY_PI;
  return res;
}