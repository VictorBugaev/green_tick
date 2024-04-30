#include "my_math.h"

long double my_asin(double x) {
  long double res = MY_NAN;
  if (x > 1 || x < -1) return res;
  if (x == 1 || x == -1) res = MY_PI / (2 * x);
  if (x > -1 && x < 1) res = MY_PI / 2 - my_acos(x);
  return res;
}