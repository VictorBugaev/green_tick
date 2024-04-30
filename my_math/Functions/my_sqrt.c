#include "my_math.h"
long double check_sqrt(double x) {
  return (x == 0) ? 0 : (x == MY_INF) ? MY_INF_POS : MY_NAN;
}
long double my_sqrt(double x) {
  long double res = check_sqrt(x);
  if (res != MY_INF) {
    if (x > 0) {
      long double x_0 = 1.0;
      for (int i = 0; i < 100; i++) {
        res = x_0 - ((x_0 * x_0 - x) / (2 * x_0));
        if (my_fabs((res - x_0)) <= 1e-14) {
          break;
        }
        x_0 = res;
      }
    }
  }
  return res;
}
