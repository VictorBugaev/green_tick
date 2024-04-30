#include "my_math.h"

long double my_log(double x) {
  double tmp = x;
  long double result = 0.0;
  long double buf = result;
  int point = 0;
  int f = 1;
  int count = 200;

  if (tmp == MY_INF_POS) {
    f = 0;
    result = tmp;
  }
  if (tmp == 0) {
    f = 0;
    result = MY_INF_NEG;
  }
  if (tmp < 0) {
    f = 0;
    result = MY_NAN;
  }
  if (f) {
    while (x > MY_E) {
      x /= MY_E;
      point += 1;
    }
    for (int i = 0; i < count; i++) {
      buf = result;
      result = buf + 2.0 * (x - my_exp(buf)) / (x + my_exp(buf));
    }
    result += point;
  }
  return result;
}