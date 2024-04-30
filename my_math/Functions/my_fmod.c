#include "my_math.h"

long double my_fmod(double x, double y) {
  long double res;
  int A = (y == 0);
  int B = MY_IS_INF(x);
  int C = MY_IS_INF(y);
  int D = (B && C && x != y);
  if (A || B || D) {
    res = MY_NAN;
  } else if (MY_IS_INF(y)) {
    res = (long double)x;
  } else {
    int n = x / y;
    res = (long double)x - n * (long double)y;
  }
  return res;
}
