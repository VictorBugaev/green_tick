#include "my_math.h"

long double my_fabs(double x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}