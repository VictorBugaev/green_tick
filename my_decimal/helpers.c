#include "my_decimal.h"

bool my_get_bit(unsigned int num, int pos) { return (num >> pos) & 1; }

void my_null_decimal(my_decimal *decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}

void my_null_big_decimal(my_big_decimal *big) {
  big->sign = 0;
  big->exp = 0;
  for (int i = 0; i < 192; i++) big->bits[i] = 0;
}

bool is_null(my_big_decimal big) {
  bool result = 0;
  for (int i = 0; i < 192; i++) result += big.bits[i];
  return !result;
}

int last_bit(my_big_decimal big) {
  int i = -1;
  if (!is_null(big)) {
    for (i = 191; i >= 0; i--)
      if (big.bits[i] == 1) break;
  }
  return i;
}

bool compare_bits(my_big_decimal big1, my_big_decimal big2) {
  int i = 191;
  while (i >= 0 && big1.bits[i] == big2.bits[i]) {
    i--;
  }
  return i == -1 ? 1 : big1.bits[i];
}

bool my_get_sign(my_decimal decimal) {
  return my_get_bit(decimal.bits[3], 31);
}

int my_decimal_get_power(my_decimal decimal) {
  return (decimal.bits[3] >> 16) & 0xFF;
}

void my_left_shift(my_decimal *value) {
  my_big_decimal big;
  my_null_big_decimal(&big);
  big = my_convert_to_big(*value);
  my_left_shift_big(&big);
  *value = my_convert_big_to_std(big);
}

void my_right_shift_big(my_big_decimal *big) {
  for (int i = 0; i < 191; i++) big->bits[i] = big->bits[i + 1];
  big->bits[191] = 0;
}

void my_left_shift_big(my_big_decimal *big) {
  for (int i = 191; i > 0; i--) big->bits[i] = big->bits[i - 1];
  big->bits[0] = 0;
}

void my_leveling_decimal(my_decimal *value_1, my_decimal *value_2) {
  my_big_decimal big_value_1 = my_convert_to_big(*value_1);
  my_big_decimal big_value_2 = my_convert_to_big(*value_2);
  my_leveling_big_decimal(&big_value_1, &big_value_2);
  *value_1 = my_convert_big_to_std(big_value_1);
  *value_2 = my_convert_big_to_std(big_value_2);
}

void my_leveling_big_decimal(my_big_decimal *big_value_1,
                              my_big_decimal *big_value_2) {
  my_big_decimal ten_power;
  int exp_dif = big_value_1->exp - big_value_2->exp;
  my_null_big_decimal(&ten_power);
  ten_power.bits[1] = 1;
  ten_power.bits[3] = 1;
  if (big_value_1->exp > big_value_2->exp) {
    for (int i = 0; i < exp_dif; i++)
      my_mul_big_decimal(*big_value_2, ten_power, big_value_2);
    if (last_bit(*big_value_2) > 95) {
      my_leveling_alt_to_smaller(big_value_1, big_value_2);
    }
    big_value_2->exp = big_value_1->exp;
  } else if (big_value_2->exp > big_value_1->exp) {
    my_leveling_big_decimal(big_value_2, big_value_1);
  }
}

void my_leveling_alt_to_smaller(my_big_decimal *value_1,
                                 my_big_decimal *value_2) {
  int mod1 = 0, mod2 = 0;
  while (last_bit(*value_2) > 95) {
    mod1 = div_by_ten(value_1);
    mod2 = div_by_ten(value_2);
  }
  my_bank_rounding(value_1, mod1);
  my_bank_rounding(value_2, mod2);
  if (last_bit(*value_2) > 95) {
    mod1 = div_by_ten(value_1);
    mod2 = div_by_ten(value_2);
    my_bank_rounding(value_1, mod1);
    my_bank_rounding(value_2, mod2);
  }
}

void my_normalize_big_decimal_exp(my_big_decimal *big_value_1,
                                   my_big_decimal *big_value_2) {
  my_big_decimal ten = {.bits = {0, 1, 0, 1}};

  my_big_decimal *larger_exp_value, *smaller_exp_value;

  if (big_value_1->exp > big_value_2->exp) {
    larger_exp_value = big_value_1;
    smaller_exp_value = big_value_2;
  } else {
    larger_exp_value = big_value_2;
    smaller_exp_value = big_value_1;
  }

  larger_exp_value->exp -= smaller_exp_value->exp;
  smaller_exp_value->exp = 0;

  while (larger_exp_value->exp != 0) {
    larger_exp_value->exp--;
    my_mul_big_decimal(*smaller_exp_value, ten, smaller_exp_value);
  }
}

int div_by_ten(my_big_decimal *big) {
  int remainder = 0;
  for (int i = 191; i >= 0; --i) {
    int cur = big->bits[i] + (remainder << 1);
    big->bits[i] = cur / 10;
    remainder = cur % 10;
  }
  big->exp--;
  return remainder;
}

void my_bank_rounding(my_big_decimal *alt, int mod) {
  if ((mod == 5 && alt->bits[0]) || mod > 5) {
    my_big_decimal one;
    my_null_big_decimal(&one);
    one.bits[0] = 1;
    one.exp = alt->exp;
    one.sign = alt->sign;
    my_add_big_decimal(*alt, one, alt);
    if (last_bit(*alt) > 95) {
      my_sub_big_decimal(*alt, one, alt);
      mod = div_by_ten(alt);
      my_bank_rounding(alt, mod);
    }
  }
}

void align(my_big_decimal *big_value_1, my_big_decimal *big_value_2) {
  if (!is_null(*big_value_1) && !is_null(*big_value_2)) {
    int l1 = last_bit(*big_value_1);
    int l2 = last_bit(*big_value_2);
    while (last_bit(*big_value_1) != last_bit(*big_value_2))
      if (compare_bits(*big_value_1, *big_value_2))
        my_left_shift_big(big_value_2);
      else
        my_left_shift_big(big_value_1);
    if (!compare_bits(*big_value_1, *big_value_2))
      my_left_shift_big(big_value_1);
    if (big_value_1->bits[0] == 0 && big_value_2->bits[0] == 0 &&
        last_bit(*big_value_1) > l1 && last_bit(*big_value_2) > l2) {
      my_right_shift_big(big_value_1);
      my_right_shift_big(big_value_2);
    }
  }
}
