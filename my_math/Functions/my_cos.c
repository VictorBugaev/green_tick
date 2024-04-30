#include "my_math.h"

long double my_cos(double num) {
  long double result = 1.0;
  int status = 1, sign = (-1);
  if (MY_IS_NAN(num) || MY_IS_INF(num)) {
    status = 0;
  } else {
    num = my_fmod(num, MY_PI * 2.0);

    if (num > (MY_PI / 2.0) && num <= MY_PI)
      num = (MY_PI - num);
    else if (num > MY_PI && num <= ((MY_PI * 3.0) / 2.0))
      num -= MY_PI;
    else if (num > ((MY_PI * 3.0) / 2.0) && num <= (MY_PI * 2.0))
      num = ((2.0 * MY_PI) - num) * (sign = 1);
    else
      sign = 1;

    long double valueTailor = 1.0;
    for (int i = 1; my_fabs(valueTailor / result) > 1e-100; i += 1)
      result += (valueTailor = ((-valueTailor) * num * num) /
                               ((2.0 * i - 1) * (2.0 * i)));
  }
  return status ? (result * sign) : MY_NAN;
}