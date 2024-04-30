#include "my_decimal_test.h"

START_TEST(from_float_to_decimal_simple) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  float number = 100.5;
  my_from_float_to_decimal(number, &decimal);
}
END_TEST

START_TEST(float_eq_float) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  float A = 100.5;
  float B = 0.0;
  my_from_float_to_decimal(A, &decimal);
  my_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(float_eq_float_minus) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  float A = -100.5;
  float B = 0.0;
  my_from_float_to_decimal(A, &decimal);
  my_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(float_eq_float_hard_test) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  float A = -1000.201;
  float B = 0.0;
  my_from_float_to_decimal(A, &decimal);
  my_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(int_decimal_int_1) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  int i = INT32_MAX, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_2) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  int i = INT32_MIN, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_3) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  int i = 0, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_4) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  int i = -123456, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_5) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  int i = 987654, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_6) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  int i = -1, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_7) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  int i = 2, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(float_decimal_float_1) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  float f = 0.0000000001, res = 0;
  my_from_float_to_decimal(f, &decimal);
  my_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

START_TEST(float_decimal_float_2) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  float f = -3.0, res = 0;
  my_from_float_to_decimal(f, &decimal);
  my_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

START_TEST(float_decimal_float_3) {
  my_decimal decimal;
  my_null_decimal(&decimal);
  float f = 0, res = 0;
  my_from_float_to_decimal(f, &decimal);
  my_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

Suite* conversion_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("conversion");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, int_decimal_int_1);
  tcase_add_test(tc_core, int_decimal_int_2);
  tcase_add_test(tc_core, int_decimal_int_3);
  tcase_add_test(tc_core, int_decimal_int_4);
  tcase_add_test(tc_core, int_decimal_int_5);
  tcase_add_test(tc_core, int_decimal_int_6);
  tcase_add_test(tc_core, int_decimal_int_7);

  tcase_add_test(tc_core, float_decimal_float_1);
  tcase_add_test(tc_core, float_decimal_float_2);
  tcase_add_test(tc_core, float_decimal_float_3);

  tcase_add_test(tc_core, from_float_to_decimal_simple);
  tcase_add_test(tc_core, float_eq_float);
  tcase_add_test(tc_core, float_eq_float_minus);
  tcase_add_test(tc_core, float_eq_float_hard_test);

  suite_add_tcase(s, tc_core);

  return s;
}
