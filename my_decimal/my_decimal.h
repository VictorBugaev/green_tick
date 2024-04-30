#ifndef SRC_MY_DECIMAL_H_
#define SRC_MY_DECIMAL_H_

#include <stdbool.h>
#include <stdio.h>

#define MINUS_SIGN 2147483648

#define MY_DEC_SIZE 4
#define MY_POSITIVE_RETURN 1
#define MY_ERROR_RETURN 0

#define MY_INT_MIN -2147483648
#define MY_INT_MAX 2147483647
#define MY_UNSIGNED_INT_MAX 4294967295
#define MY_DEC_MIN -79228162514264337593543950335
#define MY_DEC_MAX 79228162514264337593543950335

typedef struct my_decimal {
  unsigned int bits[4];
} my_decimal;

typedef struct my_big_decimal {
  bool bits[192];
  bool sign;
  int exp;
} my_big_decimal;

typedef enum {
  CONVERTATION_OK = 0,
  CONVERTATION_ERROR = 1
} convertation_result;

//===========ARITHMETICS===========

int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_add_handler(my_decimal value_1, my_decimal value_2,
                    my_decimal *result);
int my_add_big_decimal(my_big_decimal value_1, my_big_decimal value_2,
                        my_big_decimal *result);

int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_sub_handler(my_decimal value_1, my_decimal value_2,
                    my_decimal *result);
int my_sub_big_decimal(my_big_decimal value_1, my_big_decimal value_2,
                        my_big_decimal *result);

int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mul_big_decimal(my_big_decimal value_1, my_big_decimal value_2,
                        my_big_decimal *result);
int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_div_big_decimal(my_big_decimal alt_value_1,
                        my_big_decimal alt_value_2,
                        my_big_decimal *alt_result);
int handle_status(int status, int *exp, my_big_decimal *alt_result);
my_big_decimal div_with_rem(my_big_decimal alt_value_1,
                             my_big_decimal alt_value_2,
                             my_big_decimal *alt_result);

//===========COMPARISON===========

int my_is_equal(my_decimal value_1, my_decimal value_2);
int my_is_not_equal(my_decimal value_1, my_decimal value_2);
int my_is_greater(my_decimal value_1, my_decimal value_2);
int my_is_greater_or_equal(my_decimal value_1, my_decimal value_2);
int my_is_less(my_decimal value_1, my_decimal value_2);
int my_is_less_or_equal(my_decimal value_1, my_decimal value_2);

//===========CONVERTORS===========

my_big_decimal my_convert_to_big(my_decimal dec);
my_decimal my_convert_big_to_std(my_big_decimal big);

//===========HELPERS===========

bool my_get_bit(unsigned int num, int pos);
void my_null_decimal(my_decimal *decimal);
void my_null_big_decimal(my_big_decimal *big);
bool is_null(my_big_decimal big);
int last_bit(my_big_decimal big);
bool compare_bits(my_big_decimal big1, my_big_decimal big2);
bool my_get_sign(my_decimal decimal);
int my_decimal_get_power(my_decimal decimal);
void my_right_shift_big(my_big_decimal *big);
void my_left_shift_big(my_big_decimal *big);
void my_leveling_decimal(my_decimal *value_1, my_decimal *value_2);
void my_leveling_big_decimal(my_big_decimal *big_value_1,
                              my_big_decimal *big_value_2);
void my_leveling_alt_to_smaller(my_big_decimal *alt_value_1,
                                 my_big_decimal *alt_value_2);
void my_normalize_big_decimal_exp(my_big_decimal *big_value_1,
                                   my_big_decimal *big_value_2);
int div_by_ten(my_big_decimal *big);
void my_bank_rounding(my_big_decimal *alt, int mod);
void my_left_shift(my_decimal *value);
void align(my_big_decimal *big_value_1, my_big_decimal *big_value_2);

//===========CONVERSION===========

int my_from_decimal_to_float(my_decimal src, float *dst);
int my_from_decimal_to_int(my_decimal src, int *dst);
int my_from_float_to_decimal(float src, my_decimal *dst);
int my_from_int_to_decimal(int src, my_decimal *dst);

//===========OTHERS===========

int my_floor(my_decimal value, my_decimal *res);
int my_round(my_decimal value, my_decimal *res);
int my_truncate(my_decimal value, my_decimal *res);
int my_negate(my_decimal value, my_decimal *result);

#endif  // SRC_MY_DECIMAL_H_