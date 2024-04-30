#include "my_decimal.h"

int my_is_equal(my_decimal value_1, my_decimal value_2) {
  int equal = 1;
  bool value_1_is_null =
      ((value_1.bits[0] + value_1.bits[1] + value_1.bits[2]) == 0);
  bool value_2_is_null =
      ((value_2.bits[0] + value_2.bits[1] + value_2.bits[2]) == 0);
  if (!((value_1_is_null) ^ (value_2_is_null))) {
    if (my_get_sign(value_1) != my_get_sign(value_2)) {
      equal = 0;
    } else {
      my_leveling_decimal(&value_1, &value_2);
      for (int i = 0; i <= 2; i++) {
        if (value_1.bits[i] != value_2.bits[i]) {
          equal = 0;
          break;
        }
      }
    }
  } else
    equal = 0;
  return equal;
}

int my_is_not_equal(my_decimal value_1, my_decimal value_2) {
  return !my_is_equal(value_1, value_2);
}

int my_is_greater(my_decimal value_1, my_decimal value_2) {
  int greater = 0;
  bool sign1 = my_get_sign(value_1);
  bool sign2 = my_get_sign(value_2);

  bool value_1_is_null =
      ((value_1.bits[0] + value_1.bits[1] + value_1.bits[2]) == 0);
  bool value_2_is_null =
      ((value_2.bits[0] + value_2.bits[1] + value_2.bits[2]) == 0);

  if (value_1_is_null && value_2_is_null) {
    greater = 0;
  } else if ((sign1 == 0) && (sign2 == 1)) {
    greater = 1;
  } else if ((sign1 == 1) && (sign2 == 0)) {
    greater = 0;
  } else if (sign1 == sign2) {
    my_leveling_decimal(&value_1, &value_2);
    // printf("val1 = %d  val2 = %d\n", value_1.bits[0], value_2.bits[0]);
    for (int i = 2; i >= 0; i--)
      if (value_1.bits[i] > value_2.bits[i]) {
        greater = (sign1 == 1) ? 0 : 1;
        break;
      } else if (value_1.bits[i] < value_2.bits[i]) {
        greater = (sign1 == 1) ? 1 : 0;
        break;
      }
  }
  return (greater);
}

int my_is_greater_or_equal(my_decimal value_1, my_decimal value_2) {
  return my_is_greater(value_1, value_2) || my_is_equal(value_1, value_2);
}

int my_is_less(my_decimal value_1, my_decimal value_2) {
  return my_is_greater(value_2, value_1);
}

int my_is_less_or_equal(my_decimal value_1, my_decimal value_2) {
  return my_is_less(value_1, value_2) || my_is_equal(value_1, value_2);
}
