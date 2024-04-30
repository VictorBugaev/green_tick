#include "my_decimal.h"

int my_floor(my_decimal value, my_decimal *res) {
  int return_code = 0;
  if (res) {
    my_big_decimal big_value = my_convert_to_big(value);
    while (big_value.exp > 0) div_by_ten(&big_value);
    if (big_value.sign &&
        my_is_not_equal(my_convert_big_to_std(big_value), value)) {
      my_big_decimal one;
      my_null_big_decimal(&one);
      one.bits[0] = 1;
      one.sign = 1;
      my_add_big_decimal(one, big_value, &big_value);
    }
    *res = my_convert_big_to_std(big_value);
  } else {
    return_code = 1;
  }
  return return_code;
}

int my_round(my_decimal value, my_decimal *res) {
  int return_code = 0;
  if (res) {
    my_big_decimal big_value = my_convert_to_big(value);
    int mod = 0;
    while (big_value.exp > 0) mod = div_by_ten(&big_value);
    if (mod >= 5) {
      my_big_decimal one;
      my_null_big_decimal(&one);
      one.bits[0] = 1;
      one.sign = big_value.sign;
      my_add_big_decimal(one, big_value, &big_value);
    }
    *res = my_convert_big_to_std(big_value);
  } else {
    return_code = 1;
  }
  return return_code;
}

int my_truncate(my_decimal value, my_decimal *res) {
  int return_code = 0;
  if (res) {
    my_big_decimal big_value = my_convert_to_big(value);
    while (big_value.exp > 0) div_by_ten(&big_value);
    *res = my_convert_big_to_std(big_value);
  } else {
    return_code = 1;
  }
  return return_code;
}

int my_negate(my_decimal value, my_decimal *result) {
  int return_code;
  if (result) {
    return_code = 0;
    value.bits[3] ^= MINUS_SIGN;
    *result = value;
  } else {
    return_code = 1;
  }
  return return_code;
}
