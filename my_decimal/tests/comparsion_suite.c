#include "my_decimal_test.h"

START_TEST(is_equal_simple) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5123;
  second_decimal.bits[0] = 5123;
  ck_assert_int_eq(1, my_is_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_equal_0_decimal) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5123;
  ck_assert_int_eq(0, my_is_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_not_equal) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5123;
  second_decimal.bits[0] = 5123000;
  second_decimal.bits[3] = 196608;
  ck_assert_int_eq(1, my_is_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_not_equal_EQ) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5123;
  decimal.bits[3] = MINUS_SIGN;
  second_decimal.bits[0] = 5123;
  second_decimal.bits[3] = MINUS_SIGN;
  ck_assert_int_eq(0, my_is_not_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_not_equal_SIGN) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5123;
  decimal.bits[3] = MINUS_SIGN;
  second_decimal.bits[0] = 5123;
  ck_assert_int_eq(1, my_is_not_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_greater_le) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5125;
  second_decimal.bits[0] = 5123;
  second_decimal.bits[3] = MINUS_SIGN;
  ck_assert_int_eq(0, my_is_greater(second_decimal, decimal));
}
END_TEST

START_TEST(is_greater_stand) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5123;
  second_decimal.bits[0] = 5124;
  ck_assert_int_eq(1, my_is_greater(second_decimal, decimal));
}
END_TEST

START_TEST(is_greater_0) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  second_decimal.bits[0] = 5123;
  ck_assert_int_eq(0, my_is_greater(decimal, second_decimal));
}
END_TEST

START_TEST(is_greater_eq) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5123;
  second_decimal.bits[0] = 5123;
  ck_assert_int_eq(1, my_is_greater_or_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_ne) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5124;
  decimal.bits[3] = MINUS_SIGN;
  second_decimal.bits[0] = 5123;
  second_decimal.bits[3] = MINUS_SIGN;
  ck_assert_int_eq(1, my_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_equal) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5123;
  second_decimal.bits[0] = 5123;
  ck_assert_int_eq(0, my_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_Classic) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  second_decimal.bits[0] = 5123;
  ck_assert_int_eq(1, my_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_or_equal_Classic) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  decimal.bits[0] = 5123;
  second_decimal.bits[0] = 5123;
  ck_assert_int_eq(1, my_is_less_or_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_or_equal_Norm) {
  my_decimal decimal;
  my_decimal second_decimal;
  my_null_decimal(&decimal);
  my_null_decimal(&second_decimal);
  second_decimal.bits[0] = 5123;
  decimal.bits[0] = 51240;
  ck_assert_int_eq(0, my_is_less_or_equal(decimal, second_decimal));
}
END_TEST

Suite* comparsion_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("equal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, is_greater_le);
  tcase_add_test(tc_core, is_greater_stand);
  tcase_add_test(tc_core, is_greater_0);
  tcase_add_test(tc_core, is_less_ne);
  tcase_add_test(tc_core, is_less_equal);
  tcase_add_test(tc_core, is_less_Classic);
  tcase_add_test(tc_core, is_equal_simple);
  tcase_add_test(tc_core, is_equal_0_decimal);
  tcase_add_test(tc_core, is_not_equal);
  tcase_add_test(tc_core, is_not_equal_SIGN);
  tcase_add_test(tc_core, is_not_equal_EQ);
  tcase_add_test(tc_core, is_greater_eq);
  tcase_add_test(tc_core, is_less_or_equal_Classic);
  tcase_add_test(tc_core, is_less_or_equal_Norm);
  suite_add_tcase(s, tc_core);

  return s;
}
