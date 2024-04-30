#include "my_math.h"

long double my_sin(double num) {
  long double result = num;
  int status = 1, sign = (-1);
  if (num == MY_NAN || num == MY_INF) {
    status = 0;
  } else {
    num = my_fmod(num, MY_PI * 2.0);

    if (num > (MY_PI / 2.0) && num <= MY_PI)
      num = (MY_PI - num) * (sign = 1);
    else if (num > MY_PI && num <= ((MY_PI * 3.0) / 2.0))
      num -= MY_PI;
    else if (num > ((MY_PI * 3.0) / 2.0) && num <= (MY_PI * 2.0))
      num = (2.0 * MY_PI) - num;
    else
      sign = 1;

    result = (long double)num;
    long double valueTailor = (long double)num;
    for (int i = 1; my_fabs(valueTailor / result) > 1e-100; i += 1)
      result += (valueTailor = ((-valueTailor) * num * num) /
                               ((2.0 * i + 1) * (2.0 * i)));
  }
  return status ? (result * sign) : MY_NAN;
}
