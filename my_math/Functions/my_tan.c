#include "my_math.h"

long double my_tan(double num) {
  int status = 1;
  if (num == MY_NAN || num == MY_INF_POS || num == MY_INF_NEG) status = 0;
  return status ? (my_sin(num) / my_cos(num)) : MY_NAN;
}
