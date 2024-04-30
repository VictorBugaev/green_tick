#include "my_math.h"

long double my_pow(double x, double y) {
  long double res;
  int sign;
  if (x < 0) {
    sign = -1;
  } else {
    sign = 1;
  }
  if (y == 0) {
    res = 1;
  } else if (x == MY_INF_NEG && y == MY_INF_NEG) {
    res = 0;
  } else if (x == MY_INF_NEG && y == MY_INF_POS) {
    res = MY_INF_POS;
  } else if (x < 0 && y != (long long int)y) {
    res = MY_NAN;
  } else {
    res = my_exp(y * my_log(x * sign));
    if (my_fmod(y, 2)) res *= sign;
  }
  return res;
}
