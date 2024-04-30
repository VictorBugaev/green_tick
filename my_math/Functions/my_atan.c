#include "my_math.h"

long double my_pow_int(double base, long long int exp) {
  long double result = 1;
  int sign = (exp > 0);
  exp *= sign ? 1 : -1;
  for (long long int i = 0; i < exp; i++)
    result = sign ? result * base : result / base;
  return result;
}

long double my_atan(double x) {
  long double res = 0;
  if (x == MY_INF_POS) return MY_PI / 2;
  if (x == MY_INF_NEG) return -MY_PI / 2;
  if (x != x) return x;
  if (x == 1) return 0.785398163;
  if (x == -1) return -0.785398163;
  int is_in_range = (x > -1 && x < 1);
  res = is_in_range ? x : 1.0 / x;
  for (int i = 1; i < 100; i++) {
    double a = my_pow_int(-1, i);
    double b = my_pow_int(x, (1 + 2 * i) * (is_in_range ? 1 : -1));
    double c = 1 + 2 * i;
    res += a * b / c;
  }
  if (!is_in_range) res = (MY_PI * my_fabs(x) / (2 * x)) - res;
  return res;
}
