#include <check.h>
#include <string.h>

#include "../my_string.h"

START_TEST(sscanf_spec_s_1) {
  char format[] = "%s %s";
  char str[10] = "i'm tired";
  char my_str1[4], my_str2[8];
  char str1[4], str2[8];

  int res1 = my_sscanf(str, format, my_str1, my_str2);
  int res2 = sscanf(str, format, str1, str2);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(my_str1, str1);
  ck_assert_str_eq(my_str2, str2);
}
END_TEST

START_TEST(sscanf_spec_s_2) {
  char format[] = "%s";
  char str[16] = "\t\n\t\nlalalala";
  char my_str1[16];
  char str1[16];

  int res1 = my_sscanf(str, format, my_str1);
  int res2 = sscanf(str, format, str1);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(my_str1, str1);
}
END_TEST

START_TEST(sscanf_spec_s_3) {
  char format[] = "%4s";
  char str[8] = "help_me";
  char my_str1[8];
  char str1[8];

  int res1 = my_sscanf(str, format, my_str1);
  int res2 = sscanf(str, format, str1);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(my_str1, str1);
}
END_TEST

START_TEST(sscanf_spec_s_4) {
  char format[] = "%s";
  char str[8] = "%%c";
  char my_str1[8];
  char str1[8];

  int res1 = my_sscanf(str, format, my_str1);
  int res2 = sscanf(str, format, str1);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(my_str1, str1);
}
END_TEST

int wstr_cmp(const wchar_t *s1, const wchar_t *s2) {
  while (*s1 && *s1 == *s2) {
    ++s1;
    ++s2;
  }
  return *s1 - *s2;
}

START_TEST(sscanf_spec_s_5) {
  char format[] = "%ls";
  char str[16] =
      "some_test";  // используем L перед строкой для широких символов
  wchar_t my_str1[16];
  wchar_t str1[16];

  int res1 = my_sscanf(str, format, my_str1);
  int res2 = sscanf(str, format, str1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(wstr_cmp(my_str1, str1), 0);
}
END_TEST

START_TEST(sscanf_spec_c_2) {
  char format[] = "\t\n\n  %c";
  char str[] = "\t\n\n  1 \n  \t";
  char c1, c2;

  int res1 = my_sscanf(str, format, &c1);
  int res2 = sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_spec_c_4) {
  char format[] = "%c";
  char str[] = "\t\n\n   \n  \ta";
  char c1, c2;
  int res1 = my_sscanf(str, format, &c1);
  int res2 = sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_spec_c_5) {
  char format[] = "%c%c%c";
  char str[] = "\t\n\n  123 \n  \t";
  char c11, c12, c13, c21, c22, c23;

  int res1 = my_sscanf(str, format, &c11, &c12, &c13);
  int res2 = sscanf(str, format, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(sscanf_spec_c_6) {
  char format[] = "%c %c \t%c";
  char str[] = "1 2 \t3 \n  \t";
  char c11, c12, c13, c21, c22, c23;

  my_sscanf(str, format, &c11, &c12, &c13);
  sscanf(str, format, &c21, &c22, &c23);
  //  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(sscanf_spec_c_7) {
  char format[] = "%c %c \t%c";
  char str[] = "$ 1 \t23 \n  \t";
  char c11, c12, c13, c21, c22, c23;

  my_sscanf(str, format, &c11, &c12, &c13);
  sscanf(str, format, &c21, &c22, &c23);
  // ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

START_TEST(sscanf_spec_c_8) {
  char format[] = "%c %*c \t%c";
  char str[] = "1 2 \t5";
  char c11, c12, c21, c22;

  int res1 = my_sscanf(str, format, &c11, &c12);
  int res2 = sscanf(str, format, &c21, &c22);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
}
END_TEST

START_TEST(sscanf_spec_hhd_1) {
  char format[] = "%hhd";
  char str[] = "123";
  signed char d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_2) {
  char format[] = "%hhd";
  char str[] = "-123";
  signed char d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_3) {
  char format[] = "%hhd";
  char str[] = "+123";
  signed char d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_4) {
  char format[] = "%3hhd";
  char str[] = "-123";
  signed char d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_5) {
  char format[] = "%4hhd";
  char str[] = "-123";
  signed char d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_6) {
  char format[] = "%10hhd";
  char str[] = "-123";
  signed char d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_7) {
  char format[] = "%hd";
  char str[] = "-123";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_8) {
  char format[] = "%3hd";
  char str[] = "123";
  short int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_9) {
  char format[] = "%4hd";
  char str[] = "+123";
  short int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_10) {
  char format[] = "%10hd";
  char str[] = "+123";
  short int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_11) {
  char format[] = "%1hhd";
  char str[] = "123";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_12) {
  char format[] = "%*1hhd";
  char str[] = "123";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_13) {
  char format[] = "%*hhd";
  char str[] = "123";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_14) {
  char format[] = "%hd";
  char str[] = "2147483647";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_15) {
  char format[] = "%hd";
  char str[] = "+2147483647";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_16) {
  char format[] = "%hd";
  char str[] = "2147483647";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_17) {
  char format[] = "%hd";
  char str[] = "-2147483647";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_18) {
  char format[] = "%hd";
  char str[] = "-2147483647";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_19) {
  char format[] = "%hd";
  char str[] = "-214748364237";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_20) {
  char format[] = "%hd";
  char str[] = "922337477";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_21) {
  char format[] = "%hd";
  char str[] = "922337204";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_22) {
  char format[] = "%hd";
  char str[] = "9223372036";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_23) {
  char format[] = "%hd";
  char str[] = "92233720368";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_24) {
  char format[] = "%hd";
  char str[] = "92233758";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hhd_25) {
  char format[] = "%hhd";
  char str[] = "9223372032309";
  signed char d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_1) {
  char format[] = "%hd";
  char str[] = "123";
  short d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_2) {
  char format[] = "%hd";
  char str[] = "-123";
  short d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_3) {
  char format[] = "%hd";
  char str[] = "+123";
  short d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_4) {
  char format[] = "%3hd";
  char str[] = "-123";
  short d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_5) {
  char format[] = "%4hd";
  char str[] = "-123";
  short d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_6) {
  char format[] = "%10hd";
  char str[] = "-123";
  short d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_7) {
  char format[] = "%2hd";
  char str[] = "-123";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_8) {
  char format[] = "%3hd";
  char str[] = "+123";
  short d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_9) {
  char format[] = "%4hd";
  char str[] = "+123";
  short d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_10) {
  char format[] = "%10hd";
  char str[] = "+123";
  short d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_11) {
  char format[] = "%2hd";
  char str[] = "+123";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_12) {
  char format[] = "%*1hd";
  char str[] = "+123";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_13) {
  char format[] = "%*hd";
  char str[] = "123";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_14) {
  char format[] = "%hd";
  char str[] = "2147483647";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_15) {
  char format[] = "%hd";
  char str[] = "+2147483648";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_16) {
  char format[] = "%hd";
  char str[] = "214743483648";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_17) {
  char format[] = "%hd";
  char str[] = "-2147483648";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_18) {
  char format[] = "%hd";
  char str[] = "-2147483649";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_19) {
  char format[] = "%hd";
  char str[] = "-214748364239";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_20) {
  char format[] = "%hd";
  char str[] = "9223378";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_21) {
  char format[] = "%hd";
  char str[] = "9223372036854";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_22) {
  char format[] = "%hd";
  char str[] = "922337203685477";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_23) {
  char format[] = "%hd";
  char str[] = "9223372036854775807";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_24) {
  char format[] = "%hd";
  char str[] = "9223372036854775808";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_hd_25) {
  char format[] = "%hd";
  char str[] = "922337203685477582309";
  short d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_1) {
  char format[] = "%d";
  char str[] = "123";
  int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_2) {
  char format[] = "%d";
  char str[] = "-123";
  int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_3) {
  char format[] = "%d";
  char str[] = "+123";
  int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_4) {
  char format[] = "%3d";
  char str[] = "-123";
  int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_5) {
  char format[] = "%4d";
  char str[] = "-123";
  int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_6) {
  char format[] = "%10d";
  char str[] = "-123";
  int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_7) {
  char format[] = "%2d";
  char str[] = "-123";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_8) {
  char format[] = "%3d";
  char str[] = "+123";
  int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_9) {
  char format[] = "%4d";
  char str[] = "+123";
  int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_10) {
  char format[] = "%10d";
  char str[] = "+123";
  int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_11) {
  char format[] = "%2d";
  char str[] = "+123";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_12) {
  char format[] = "%*1d";
  char str[] = "+123";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_13) {
  char format[] = "%*d";
  char str[] = "123";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_14) {
  char format[] = "%d";
  char str[] = "2147483647";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_15) {
  char format[] = "%d";
  char str[] = "+2147483648";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_16) {
  char format[] = "%d";
  char str[] = "214743483648";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_17) {
  char format[] = "%d";
  char str[] = "-2147483648";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_18) {
  char format[] = "%d";
  char str[] = "-2147483649";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_19) {
  char format[] = "%d";
  char str[] = "-214748364239";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_20) {
  char format[] = "%d";
  char str[] = "9223372036854775808";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_21) {
  char format[] = "%d";
  char str[] = "9223372036854775809";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_22) {
  char format[] = "%d";
  char str[] = "922337203685477582309";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_23) {
  char format[] = "%d";
  char str[] = "9223372036854775807";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_24) {
  char format[] = "%d";
  char str[] = "9223372036854775808";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_d_25) {
  char format[] = "%d";
  char str[] = "922337203685477582309";
  int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_1) {
  char format[] = "%ld";
  char str[] = "123";
  long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_2) {
  char format[] = "%ld";
  char str[] = "-123";
  long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_3) {
  char format[] = "%ld";
  char str[] = "+123";
  long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_4) {
  char format[] = "%3ld";
  char str[] = "-123";
  long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_5) {
  char format[] = "%4ld";
  char str[] = "-123";
  long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_6) {
  char format[] = "%10ld";
  char str[] = "-123";
  long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_7) {
  char format[] = "%2ld";
  char str[] = "-123";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_8) {
  char format[] = "%3ld";
  char str[] = "+123";
  long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_9) {
  char format[] = "%4ld";
  char str[] = "+123";
  long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_10) {
  char format[] = "%10ld";
  char str[] = "+123";
  long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_11) {
  char format[] = "%2ld";
  char str[] = "+123";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_12) {
  char format[] = "%*1ld";
  char str[] = "+123";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_13) {
  char format[] = "%*ld";
  char str[] = "123";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_14) {
  char format[] = "%ld";
  char str[] = "2147483647";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_15) {
  char format[] = "%ld";
  char str[] = "+2147483648";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_16) {
  char format[] = "%ld";
  char str[] = "214743483648";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_17) {
  char format[] = "%ld";
  char str[] = "-2147483648";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_18) {
  char format[] = "%ld";
  char str[] = "-2147483649";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_19) {
  char format[] = "%ld";
  char str[] = "-214748364239";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_20) {
  char format[] = "%ld";
  char str[] = "9223372036854775808";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_21) {
  char format[] = "%ld";
  char str[] = "9223372036854775809";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_22) {
  char format[] = "%ld";
  char str[] = "922337203685477582309";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_23) {
  char format[] = "%ld";
  char str[] = "9223372036854775807";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_24) {
  char format[] = "%ld";
  char str[] = "9223372036854775808";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_ld_25) {
  char format[] = "%ld";
  char str[] = "922337203685477582309";
  long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_1) {
  char format[] = "%lld";
  char str[] = "123";
  long long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_2) {
  char format[] = "%lld";
  char str[] = "-123";
  long long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_3) {
  char format[] = "%lld";
  char str[] = "+123";
  long long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_4) {
  char format[] = "%3lld";
  char str[] = "-123";
  long long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_5) {
  char format[] = "%4lld";
  char str[] = "-123";
  long long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_6) {
  char format[] = "%10lld";
  char str[] = "-123";
  long long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_7) {
  char format[] = "%2lld";
  char str[] = "-123";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_8) {
  char format[] = "%3lld";
  char str[] = "+123";
  long long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_9) {
  char format[] = "%4lld";
  char str[] = "+123";
  long long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_10) {
  char format[] = "%10lld";
  char str[] = "+123";
  long long int d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_11) {
  char format[] = "%2lld";
  char str[] = "+123";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_12) {
  char format[] = "%*1lld";
  char str[] = "+123";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_13) {
  char format[] = "%*lld";
  char str[] = "123";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_14) {
  char format[] = "%lld";
  char str[] = "2147483647";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_15) {
  char format[] = "%lld";
  char str[] = "+2147483648";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_16) {
  char format[] = "%lld";
  char str[] = "214743483648";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_17) {
  char format[] = "%lld";
  char str[] = "-2147483648";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_18) {
  char format[] = "%lld";
  char str[] = "-2147483649";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_19) {
  char format[] = "%lld";
  char str[] = "-214748364239";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_20) {
  char format[] = "%lld";
  char str[] = "9223372036854775808";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_21) {
  char format[] = "%lld";
  char str[] = "9223372036854775809";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_22) {
  char format[] = "%lld";
  char str[] = "922337203685477582309";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_23) {
  char format[] = "%lld";
  char str[] = "9223372036854775807";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_24) {
  char format[] = "%lld";
  char str[] = "9223372036854775808";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_lld_25) {
  char format[] = "%lld";
  char str[] = "922337203685477582309";
  long long int d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_empty_1) {
  char format[] = "";
  char str[] = "";
  int p1, p2;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_2) {
  char format[] = "%d";
  char str[] = "uaishf";
  int p1, p2;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_3) {
  char format[] = "";
  char str[] = "ahgsdfjhga";
  int p1, p2;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_5) {
  char format[] = "\t\n\n";
  char str[] = "\t\n\n   \n  \t";
  int p1, p2;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_6) {
  char format[] = "";
  char str[] = "\t\n\n   \n  \t";
  int p1, p2;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_empty_7) {
  char format[] = "\t";
  char str[] = "\t\n\n   \n  \t";
  int p1, p2;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_1) {
  char format[] = "%hi %hi %hi";
  char str[] = "123 +198 -87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_6) {
  char format[] = "%30hi %24hi %21hi";
  char str[] = "13 +137 -8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_7) {
  char format[] = "%hi %hi %hi %hi";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_8) {
  char format[] = "%hi %hi %hi -%hi";
  char str[] =
      "9223372036854775807 +9223372036854775808 -922337203685477580 "
      "-9223372036854775808";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_1) {
  char format[] = "%hi %hi%hi";
  char str[] = "0123 +0198 -087";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_6) {
  char format[] = "%30hi %24hi %21hi";
  char str[] = "013 +0137 -08";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_7) {
  char format[] = "%hi %hi %hi %hi";
  char str[] = "037777777777 +040000000000 -040000000000 040000001";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_oct_8) {
  char format[] = "%hi %hi %hi %hi";
  char str[] =
      "01777777777777777777777 +020000000000000000000 -02000000000000000000000 "
      "020000000000000001";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_1) {
  char format[] = "%hi %hi %hi";
  char str[] = "0x123 +0X198 0x87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_6) {
  char format[] = "%30hi %24hi %21hi";
  char str[] = "0x13 +0x1a 0x8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_7) {
  char format[] = "%hi %hi %hi %hi";
  char str[] = "0xffffffff +0xffffffeab 0xFfFfffFf 0x39cdb3aa";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_hex_8) {
  char format[] = "%hi %hi %hi %hi";
  char str[] = "0xFFFFFFFFFFF 0x800000000000 0xFFFFFFFFFFFF 0x348923848239";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_1) {
  char format[] = "%i %i %i";
  char str[] = "123 +198 -87";
  int d1, d2;
  int q1, q2;
  int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_2) {
  char format[] = "%i %i %i";
  char str[] = "123 +198 -87";
  int d1, d2;
  int q1, q2;
  int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_3) {
  char format[] = "%1i%1i +%1i";
  char str[] = "13 +137 -8";
  int d1, d2;
  int q1, q2;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_4) {
  char format[] = "%2i +%3i %2i";
  char str[] = "13 +137 -8";
  int d1, d2;
  int q1, q2;
  int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_5) {
  char format[] = "%3i +%3i %3i";
  char str[] = "13 +137 -8";
  int d1, d2;
  int q1, q2;
  int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_6) {
  char format[] = "%30i %24i %21i";
  char str[] = "13 +137 -8";
  int d1, d2;
  int q1, q2;
  int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_7) {
  char format[] = "%i %i %i %i";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  int d1, d2;
  int q1, q2;
  int z1, z2;
  int w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_8) {
  char format[] = "%i %i %i %i";
  char str[] =
      "92233720368547758 +9223372036854775808 -9223372036854775807 "
      "-922337203685477587";
  int d1, d2;
  int q1, q2;
  int z1, z2;
  int w1, w2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_i_oct_1) {
  char format[] = "%i %i%*d %i";
  char str[] = "0123 0198 078";
  int d1, d2;
  int q1, q2;
  int z1, z2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_oct_6) {
  char format[] = "%30i +%24i -%21i";
  char str[] = "013 +0137 -018";
  int d1, d2;
  int q1, q2;
  int z1, z2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_oct_7) {
  char format[] = "%i +%i -%i -%i";
  char str[] = "037777777777 +040000000000 -040000000000 -040000000001";
  int d1, d2;
  int q1, q2;
  int z1, z2;
  int w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_i_oct_8) {
  char format[] = "%i +%i -%i %i";
  char str[] =
      "01777777777777777777777 +020000000000000000000 -020000000000000000000 "
      "-02000000000000000000000";
  int d1, d2;
  int q1, q2;
  int z1, z2;
  int w1, w2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_i_hex_1) {
  char format[] = "%i %i -%i";
  char str[] = "0x123 +0X198 -0x87";
  int d1, d2;
  int q1, q2;
  int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_hex_6) {
  char format[] = "%30i %24i %21i";
  char str[] = "0x13 +0x1a 0x8";
  int d1, d2;
  int q1, q2;
  int z1, z2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_hex_7) {
  char format[] = "%i %i %i %i";
  char str[] = "0xffffffff +0xffffffeab 0xFfFfffFf 0x39cdb3aa";
  int d1, d2;
  int q1, q2;
  int z1, z2;
  int w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_i_hex_8) {
  char format[] = "%i %i %i %i";
  char str[] = "0xFFFFFFFFFFF 0x8000000000000 0xFFFFFFFFFFFFF 0x34892384823974";
  int d1, d2;
  int q1, q2;
  int z1, z2;
  int w1, w2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_1) {
  char format[] = "%li %li %li";
  char str[] = "123 +198 87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_6) {
  char format[] = "%30li %24li %21li";
  char str[] = "13 +137 8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_7) {
  char format[] = "%li %li %li %li";
  char str[] = "2147483647 +2147483648 2147483648 2147483649";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_8) {
  char format[] = "%li %li %li -%li";
  char str[] =
      "922337203685477580 92233720368547758 922337203687 -922337203685477580";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;
  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_li_oct_1) {
  char format[] = "%li %li %li";
  char str[] = "0123 +01 98 -087";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_oct_6) {
  char format[] = "%30li +%24li %21li";
  char str[] = "013 +0137 -08";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_oct_7) {
  char format[] = "%li %li %li";
  char str[] = "037777777777 +0400000000 04000000";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_oct_8) {
  char format[] = "%li +%li %li %li";
  char str[] = "015654562 +02000000000 022356250000 022000001";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_li_hex_1) {
  char format[] = "%li %li %li";
  char str[] = "0x123 +0X198 0x87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_hex_6) {
  char format[] = "%30li %24li %21li";
  char str[] = "0x13 +0x1a 0x8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_hex_7) {
  char format[] = "%li %li %li %li";
  char str[] = "0xffffffff +0xffffffab 0xFfFfffFf 0x39cdb3aa";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_n_1) {
  char format[] = "%*s%n";
  char str[] = "Ilyusha";
  int n1 = 0, n2 = 0;

  int res1 = my_sscanf(str, format, &n1);
  int res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_spec_n_2) {
  char format[] = "%d %n";
  char str[] = "80 Ilyusha";
  int d1 = 0, d2 = 0;
  int n1 = 0, n2 = 0;

  int res1 = my_sscanf(str, format, &d1, &n1);
  int res2 = sscanf(str, format, &d2, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_spec_n_3) {
  char format[] = "%d %d %n%d %d %d";
  char str[] = "80 50 70 371 327";
  int d1 = 0, d2 = 0;
  int dd1 = 0, dd2 = 0;
  int f1 = 0, f2 = 0;
  int ff1 = 0, ff2 = 0;
  int k1 = 0, k2 = 0;
  int n1 = 0, n2 = 0;

  int res1 = my_sscanf(str, format, &d1, &dd1, &n1, &f1, &ff1, &k1);
  int res2 = sscanf(str, format, &d2, &dd2, &n2, &f2, &ff2, &k2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(dd1, dd2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(ff1, ff2);
  ck_assert_int_eq(k1, k2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_spec_n_4) {
  char format[] = "Hello%n";
  char str[] = "Hello";
  int *n1 = 0, *n2 = 0;

  int res1 = my_sscanf(str, format, &n1);
  int res2 = sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_spec_n_5) {
  char format[] = "%d %hn%d %hhn%d %d %hhn%d";
  char str[] = "80 50 70 371 327";
  int d1 = 0, d2 = 0;
  int dd1 = 0, dd2 = 0;
  int f1 = 0, f2 = 0;
  int ff1 = 0, ff2 = 0;
  int k1 = 0, k2 = 0;
  short hn1 = 0, hn2 = 0;
  int hhn1 = 0, hhn2 = 0;
  int n1 = 0, n2 = 0;

  int res1 =
      my_sscanf(str, format, &d1, &hn1, &dd1, &hhn1, &f1, &ff1, &n1, &k1);
  int res2 = sscanf(str, format, &d2, &hn2, &dd2, &hhn2, &f2, &ff2, &n2, &k2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(dd1, dd2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(ff1, ff2);
  ck_assert_int_eq(k1, k2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(hn1, hn2);
  ck_assert_int_eq(hhn1, hhn2);
}
END_TEST

START_TEST(sscanf_spec_n_6) {
  char format[] = "%d%ln %d%lln %d %d%lln %d";
  char str[] = "3263 225 724 38 482";
  int d1 = 0, d2 = 0;
  int dd1 = 0, dd2 = 0;
  int f1 = 0, f2 = 0;
  int ff1 = 0, ff2 = 0;
  int k1 = 0, k2 = 0;
  long int hn1 = 0, hn2 = 0;
  long long int hhn1 = 0, hhn2 = 0;
  long long int n1 = 0, n2 = 0;

  int res1 =
      my_sscanf(str, format, &d1, &hn1, &dd1, &hhn1, &f1, &ff1, &n1, &k1);
  int res2 = sscanf(str, format, &d2, &hn2, &dd2, &hhn2, &f2, &ff2, &n2, &k2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(dd1, dd2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(ff1, ff2);
  ck_assert_int_eq(k1, k2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(hn1, hn2);
  ck_assert_int_eq(hhn1, hhn2);
}
END_TEST

START_TEST(sscanf_spec_n_7) {
  char format[] = "%%%c";
  char str[] = "%p";
  char d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_n_8) {
  char format[] = "%s %n%s %n%s %s %s%n";
  char str[] = "Hello, my name is Jinny";
  char s1[30], s2[30], s3[30], s4[30], s5[30], s6[30], s7[30], s8[30], s9[30],
      s10[30];
  int n1 = 0, n2 = 0;
  int hn1 = 0, hn2 = 0;
  int hhn1 = 0, hhn2 = 0;

  int res1 = my_sscanf(str, format, &s1, &hn1, &s3, &hhn1, &s5, &s7, &s9, &n1);
  int res2 = sscanf(str, format, &s2, &hn2, &s4, &hhn2, &s6, &s8, &s10, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_pstr_eq(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  ck_assert_pstr_eq(s5, s6);
  ck_assert_pstr_eq(s7, s8);
  ck_assert_pstr_eq(s9, s10);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(hn1, hn2);
  ck_assert_int_eq(hhn1, hhn2);
}
END_TEST

START_TEST(sscanf_spec_n_9) {
  char format[] = "%lf %lf %lf %lf%n %lf";
  char str[] = ".0 66.34 9877.66 1.99 0.999";
  long double d1 = 0, d2 = 0;
  long double dd1 = 0, dd2 = 0;
  long double f1 = 0, f2 = 0;
  long double ff1 = 0, ff2 = 0;
  long double k1 = 0, k2 = 0;
  int n1 = 0, n2 = 0;

  int res1 = my_sscanf(str, format, &d1, &dd1, &f1, &ff1, &n1, &k1);
  int res2 = sscanf(str, format, &d2, &dd2, &f2, &ff2, &n2, &k2);
  ck_assert_ldouble_eq(res1, res2);
  ck_assert_ldouble_eq(d1, d2);
  ck_assert_ldouble_eq(dd1, dd2);
  ck_assert_ldouble_eq(f1, f2);
  ck_assert_ldouble_eq(ff1, ff2);
  ck_assert_ldouble_eq(k1, k2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_spec_n_10) {
  char format[] = "%s %s";
  char str[] = "hi \t\n";
  char s1[20], s2[20] = {0}, s3[20], s4[20] = {0};

  int res1 = my_sscanf(str, format, s1, s2);
  int res2 = sscanf(str, format, s3, s4);
  ck_assert_ldouble_eq(res1, res2);
  ck_assert_pstr_eq(s1, s3);
  ck_assert_pstr_eq(s2, s4);
}
END_TEST

START_TEST(sscanf_spec_hho_1) {
  char format[] = "%ho %ho%*d %ho";
  char str[] = "123 19 16";
  short int d1, d2;
  short int q1, q2;
  short int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(q1, q2);
  ck_assert_int_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hho_2) {
  char format[] = "%ho %ho %ho";
  char str[] = "123 1564 1723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hho_3) {
  char format[] = "%1hho %3hho %3hho";
  char str[] = "1 +04 3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hho_4) {
  char format[] = "%2hho%2hho %3hho";
  char str[] = "0123 +04 -3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hho_5) {
  char format[] = "%4hho %3hho -%3hho";
  char str[] = "0123 +04 -3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hho_6) {
  char format[] = "%*hho %*hho %*hho";
  char str[] = "0123 +04 -3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_ho_1) {
  char format[] = "%ho %ho %ho";
  char str[] = "123 +198 -87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_ho_2) {
  char format[] = "%ho %ho -%ho";
  char str[] = "123 +1564 -1723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_ho_3) {
  char format[] = "%1ho %3ho -%3ho";
  char str[] = "1 +04 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_ho_4) {
  char format[] = "%2ho%2ho %3ho";
  char str[] = "0123 +04 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_ho_5) {
  char format[] = "%4ho %3ho -%3ho";
  char str[] = "0123 +04 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_ho_6) {
  char format[] = "%*ho %*ho %*ho";
  char str[] = "0123 +04 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_o_1) {
  char format[] = "%o %o %o";
  char str[] = "123 +198 -87";
  int d1, d2;
  int q1, q2;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_o_2) {
  char format[] = "%o %o %o";
  char str[] = "123 +1564 1723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_o_3) {
  char format[] = "%1o %3o %3o";
  char str[] = "1 +04 3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_o_4) {
  char format[] = "%2o%2o %3o";
  char str[] = "0123 +04 -3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_o_5) {
  char format[] = "%4o %3o %3o";
  char str[] = "0123 +04 3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_o_6) {
  char format[] = "%*o %*o %*o";
  char str[] = "0123 +04 -3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_1) {
  char format[] = "%lo %lo %lo";
  char str[] = "123 +198 -87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_2) {
  char format[] = "%lo %lo %lo";
  char str[] = "123 +1564 1723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_3) {
  char format[] = "%1lo %3lo %5lo";
  char str[] = "1 +04 3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_4) {
  char format[] = "%2lo%2lo %lo";
  char str[] = "0123 +04 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_5) {
  char format[] = "%4lo %3lo -%lo";
  char str[] = "0123 +04 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lo_6) {
  char format[] = "%*lo %*lo %*lo";
  char str[] = "0123 +04 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llo_1) {
  char format[] = "%llo %llo %llo";
  char str[] = "123 +198 -87";
  unsigned long long int d1, d2;
  unsigned long long int q1, q2;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llo_2) {
  char format[] = "%llo %llo -%llo";
  char str[] = "123 +1564 -1723";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llo_3) {
  char format[] = "%1llo %llo -%llo";
  char str[] = "1 +04 -3723";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llo_4) {
  char format[] = "%2llo%2llo +%llo";
  char str[] = "0123 +04 -3723";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llo_5) {
  char format[] = "%4llo %llo -%llo";
  char str[] = "0123 +04 -3723";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llo_6) {
  char format[] = "%*llo %*llo %*llo";
  char str[] = "0123 +04 -3723";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_p_1) {
  char format[] = "%p";
  char str[] = "0xAAAA";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_2) {
  char format[] = "%5p";
  char str[] = "0xAAAA";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_3) {
  char format[] = "%p";
  char str[] = "0xFFFFFF";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_4) {
  char format[] = "%p";
  char str[] = "0x0000";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_5) {
  char format[] = "%p";
  char str[] = "0xA2361598";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_6) {
  char format[] = "%p";
  char str[] = "0x34567hjk";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_7) {
  char format[] = "%p";
  char str[] = "0x34567hjk678";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_8) {
  char format[] = "%p";
  char str[] = "0x34abCD68";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_9) {
  char format[] = "%p";
  char str[] = "0x245ab7";
  void *p1 = 0, *p2 = 0;

  int res2 = sscanf(str, format, &p2);
  int res1 = my_sscanf(str, format, &p1);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_10) {
  char format[] = "%p";
  char str[] = "0x237481";
  void *p1 = 0, *p2 = 0;
  int res2 = sscanf(str, format, &p2);
  int res1 = my_sscanf(str, format, &p1);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_11) {
  char format[] = "%6p";
  char str[] = "0xdksajh";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_12) {
  char format[] = "%6p";
  char str[] = "0xAGAGUIY";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_13) {
  char format[] = "%p";
  char str[] = "0xAGAGUIYUYGFSV";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_14) {
  char format[] = "%p";
  char str[] = "0xAA64BB";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_15) {
  char format[] = "%p";
  char str[] = "0xabGGHTY";
  void *p1 = 0, *p2 = 0;

  int res1 = my_sscanf(str, format, &p1);
  int res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_f_1) {
  char format[] = "%f %f %f";
  char str[] = "123 +198 -87";
  float d1, d2;
  float q1, q2;
  float z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_f_2) {
  char format[] = "%fg %fw %fx";
  char str[] = "75g +19.8w -87.x";
  float d1, d2;
  float q1, q2;
  float z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_f_3) {
  char format[] = "%f %f %f %f";
  char str[] = "NAN nan INF +inf";
  float d1, d2;
  float q1, q2;
  float z1, z2;
  float w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(d1);
  ck_assert_float_nan(d2);
  ck_assert_float_nan(q1);
  ck_assert_float_nan(q2);
  ck_assert_float_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_f_4) {
  char format[] = "%f";
  char str[] = "heks";
  float d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_f_5) {
  char format[] = "%f";
  char str[] = "nann";
  float d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(d1);
}
END_TEST

START_TEST(sscanf_spec_f_6) {
  char format[] = "%f";
  char str[] = "iNf";
  float d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_f_7) {
  char format[] = "%f";
  char str[] = "id";
  float d1 = 0, d2 = 0;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_f_8) {
  char format[] = "%f %f %f %f";
  char str[] = "34.56e3 83.2e-4 .43e+1 +2.43e3";
  float d1, d2;
  float q1, q2;
  float z1, z2;
  float w1, w2;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_f_9) {
  char format[] = "%1f%1f%2f+%1f";
  char str[] = "34.5+6e3 83.2e-4 .43e+1 +2.43e3";
  float d1, d2;
  float q1, q2;
  float z1, z2;
  float w1 = 0, w2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_f_10) {
  char format[] = "%*f %f %*f %*f";
  char str[] = "34.5 +6e3 83.2e-4 +43e+1 +2.43e3";
  float d1, d2;

  int res1 = my_sscanf(str, format, &d1);
  int res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_f_11) {
  char format[] = "%fr %7f p";
  char str[] = "34.5r 83.2ep4";
  float d1, d2;
  float q1 = 0, q2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1);
  int res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_f_12) {
  char format[] = "%1f%1f %1f%1f";
  char str[] = "34 32. +45.e +23E3 -0.3e4";
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_f_13) {
  char format[] = "%2f %2f %2f%2f";
  char str[] = "34 3. +45.e +23E3 -0.3e4";
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_f_14) {
  char format[] = "%3f %3f %4f %3f";
  char str[] = "34 3. +45.e +23E3 -0.3e4";
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_f_15) {
  char format[] = "%4f %4f %4f %4f";
  char str[] = "34 3. +45.e +23E3 -0.3e4";
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_f_18) {
  char format[] = "%f %fx %2f1 %2fx %*f %*f";
  char str[] = "1.1 2.x 1.1 2.x 1.1 2.x";
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_f_19) {
  char format[] = "%f %4f %5fq %6f %*f q%*f";
  char str[] = "1.3e1 1.4eq2 1.3e1q 1.4 1.3eq 1.4e2";
  float d1, d2;
  float q1 = 0, q2 = 0;
  float z1 = 0, z2 = 0;
  float w1 = 0, w2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1, &w1);
  int res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
  ck_assert_float_eq(w1, w2);
}
END_TEST
START_TEST(sscanf_spec_hhx_1) {
  char format_1[] = "%hx %hx %hx";
  char format_2[] = "%hx %hx %hx";
  char str_1[] = "123 198 87";
  const char *str_1_ptr = str_1;
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str_1_ptr, format_1, &d1, &q1, &z1);
  int res2 = sscanf(str_1, format_2, &d2, &q2, &z2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(q1, q2);
  ck_assert_int_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhx_2) {
  char format[] = "%hx %hx %hx";
  char str[] = "12a3 +156B4 17C23";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(q1, q2);
  ck_assert_int_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhx_3) {
  char format[] = "%hxX%hx";
  char str[] = "0X32 0X11";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1);
  int res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_hhx_4) {
  char format[] = "%hxx%hx %hx";
  char str[] = "0x42a 0XABC 0X24";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhx_5) {
  char format[] = "%hxx%hx %hx";
  char str[] = "0xabc4 0XABC 0x123";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhx_6) {
  char format[] = "%1hx%1hx %1hx";
  char str[] = "1a 04 -3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhx_7) {
  char format[] = "%hx %hx %hx";
  char str[] = "1a 0x1 3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhx_8) {
  char format[] = "%hx %hx %hx";
  char str[] = "1a bc 0x14 -3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhx_9) {
  char format[] = "%hx %hx %hx";
  char str[] = "1a bCc 0x17 -3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhx_10) {
  char format[] = "%hx %hx %hx";
  char str[] = "0x123 +0X4 37x23";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhx_11) {
  char format[] = "%*hx %*hx %*hx";
  char str[] = "0x123 +04 -372f3";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_1) {
  char format[] = "%hx %hx %hx";
  char str[] = "123 +198 87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_2) {
  char format[] = "%hx %hx %hx";
  char str[] = "12a3 +156B4 17C23";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_3) {
  char format[] = "%hx %hx";
  char str[] = "0 +0x1";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1);
  int res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_hx_4) {
  char format[] = "%hx %hx %hx";
  char str[] = "0 0XABC 0X34";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_5) {
  char format[] = "%hx %hx %hx";
  char str[] = "0abc4 0XABC 0x1";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_6) {
  char format[] = "%1hx%1hx +%1hx";
  char str[] = "1a +04 3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_7) {
  char format[] = "%1hx%1hx 0x%1hx";
  char str[] = "1a 0x1 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_8) {
  char format[] = "%2hx %2hx %3hx";
  char str[] = "1a bc 0x1 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_9) {
  char format[] = "%2hx %hx %3hx";
  char str[] = "1a bCc 0x1 -3723";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_10) {
  char format[] = "%hx %4hx %2hx";
  char str[] = "0x123 +0X4 37x23";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hx_11) {
  char format[] = "%*hx %*hx %*hx";
  char str[] = "0x123 +04 -372f3";
  unsigned short d1 = 0, d2 = 0;
  unsigned short q1 = 0, q2 = 0;
  unsigned short z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_1) {
  char format[] = "%x %x %x";
  char str[] = "123 +198 87";
  int d1, d2;
  int q1, q2;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_2) {
  char format[] = "%x %x %x";
  char str[] = "12a3 +156B4 17C23";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_3) {
  char format[] = "%x %x";
  char str[] = "0 +0x1";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1);
  int res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_x_4) {
  char format[] = "%x %x %x";
  char str[] = "0 0XABC 0X1";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_5) {
  char format[] = "%x %x %x";
  char str[] = "0abc4 0XABC 0x1";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_6) {
  char format[] = "%2x %3x %x";
  char str[] = "1a +04 3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_7) {
  char format[] = "%2x %3x %2x";
  char str[] = "1a 0x1 3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_8) {
  char format[] = "%2x %2x %3x";
  char str[] = "1a bc 0x1 3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_9) {
  char format[] = "%2x %3x %3x";
  char str[] = "1a bCc 0x1 3723";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_10) {
  char format[] = "%5x %4x %4x";
  char str[] = "0x123 +0X4 37x23";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_x_11) {
  char format[] = "%*x %*x %*x";
  char str[] = "0x123 +04 -372f3";
  int d1 = 0, d2 = 0;
  int q1 = 0, q2 = 0;
  int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_1) {
  char format[] = "%lx %lx %lx";
  char str[] = "123 +198 87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_2) {
  char format[] = "%lx %lx %lx";
  char str[] = "12a3 +156B4 17C23";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_3) {
  char format[] = "%lx %lx";
  char str[] = "0 +0x1";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1);
  int res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_lx_4) {
  char format[] = "%lx %lx %lx";
  char str[] = "0 0XABC 0X1";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_5) {
  char format[] = "%lx %lx %lx";
  char str[] = "0abc4 0XABC 0x1";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_6) {
  char format[] = "%2lx %3lx %2lx";
  char str[] = "1a +04 3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_7) {
  char format[] = "%2lx %3lx %1lx";
  char str[] = "1a 0x1 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_8) {
  char format[] = "%2lx %2lx %3lx";
  char str[] = "1a bc 0x1 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_9) {
  char format[] = "%2lx %3lx %3lx";
  char str[] = "1a bCc 0x1 -3723";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_10) {
  char format[] = "%5lx %4lx %3lx";
  char str[] = "0x123 +0X4 37x23";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lx_11) {
  char format[] = "%*lx %*lx %*lx";
  char str[] = "0x123 +04 -372f3";
  unsigned long int d1 = 0, d2 = 0;
  unsigned long int q1 = 0, q2 = 0;
  unsigned long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_1) {
  char format[] = "%llx %llx %llx";
  char str[] = "123 +198 87";
  unsigned long long int d1, d2;
  unsigned long long int q1, q2;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_2) {
  char format[] = "%llx %llx %llx";
  char str[] = "12a3 +156B4 17C23";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_3) {
  char format[] = "%llx %llx";
  char str[] = "0 +0x1";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1);
  int res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_llx_4) {
  char format[] = "%llx %llx %llx";
  char str[] = "0 0XABC 0X1";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_5) {
  char format[] = "%llx %llx %llx";
  char str[] = "0abc4 0XABC 0x1";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_6) {
  char format[] = "%1llx%1llx %2llx";
  char str[] = "1a +04 -3723";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_7) {
  char format[] = "%2llx %3llx -%llx";
  char str[] = "1a 0x1 -3723";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_8) {
  char format[] = "%2llx %2llx %3llx";
  char str[] = "1a bc 0x1 -3723";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_9) {
  char format[] = "%2llx %2llx%*x %3llx";
  char str[] = "1a bCc 0x1 -3723";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_10) {
  char format[] = "%llx %4llx %3llx";
  char str[] = "0x123 +0X4 37x23";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_llx_11) {
  char format[] = "%*llx %*llx %*llx";
  char str[] = "0x123 +04 -372f3";
  unsigned long long int d1 = 0, d2 = 0;
  unsigned long long int q1 = 0, q2 = 0;
  unsigned long long int z1 = 0, z2 = 0;

  int res1 = my_sscanf(str, format, &d1, &q1, &z1);
  int res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(test_11_sscanf) {
  char s[20] = "2.4E-3 e3lalaley";
  long double g = 0;
  char first[10] = {0};
  char format[10] = "%Le %s";
  my_sscanf(s, format, &g, first);
  char a[20] = "2.4E-3 e3lalaley";
  long double m = 0;
  char second[10] = {0};
  char format2[10] = "%Le %s";
  sscanf(a, format2, &m, second);
  ck_assert_int_eq(g, m);
  ck_assert_str_eq(first, second);
}
END_TEST

Suite *test_sscanf_d(void) {
  Suite *s = suite_create("S21 SSCANF D");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_hhd_1);
  tcase_add_test(tc, sscanf_spec_hhd_2);
  tcase_add_test(tc, sscanf_spec_hhd_3);
  tcase_add_test(tc, sscanf_spec_hhd_4);
  tcase_add_test(tc, sscanf_spec_hhd_5);
  tcase_add_test(tc, sscanf_spec_hhd_6);
  tcase_add_test(tc, sscanf_spec_hhd_7);
  tcase_add_test(tc, sscanf_spec_hhd_8);
  tcase_add_test(tc, sscanf_spec_hhd_9);
  tcase_add_test(tc, sscanf_spec_hhd_10);
  tcase_add_test(tc, sscanf_spec_hhd_11);
  tcase_add_test(tc, sscanf_spec_hhd_12);
  tcase_add_test(tc, sscanf_spec_hhd_13);
  tcase_add_test(tc, sscanf_spec_hhd_14);
  tcase_add_test(tc, sscanf_spec_hhd_15);
  tcase_add_test(tc, sscanf_spec_hhd_16);
  tcase_add_test(tc, sscanf_spec_hhd_17);
  tcase_add_test(tc, sscanf_spec_hhd_18);
  tcase_add_test(tc, sscanf_spec_hhd_19);
  tcase_add_test(tc, sscanf_spec_hhd_20);
  tcase_add_test(tc, sscanf_spec_hhd_21);
  tcase_add_test(tc, sscanf_spec_hhd_22);
  tcase_add_test(tc, sscanf_spec_hhd_23);
  tcase_add_test(tc, sscanf_spec_hhd_24);
  tcase_add_test(tc, sscanf_spec_hhd_25);

  tcase_add_test(tc, sscanf_spec_hd_1);
  tcase_add_test(tc, sscanf_spec_hd_2);
  tcase_add_test(tc, sscanf_spec_hd_3);
  tcase_add_test(tc, sscanf_spec_hd_4);
  tcase_add_test(tc, sscanf_spec_hd_5);
  tcase_add_test(tc, sscanf_spec_hd_6);
  tcase_add_test(tc, sscanf_spec_hd_7);
  tcase_add_test(tc, sscanf_spec_hd_8);
  tcase_add_test(tc, sscanf_spec_hd_9);
  tcase_add_test(tc, sscanf_spec_hd_10);
  tcase_add_test(tc, sscanf_spec_hd_11);
  tcase_add_test(tc, sscanf_spec_hd_12);
  tcase_add_test(tc, sscanf_spec_hd_13);
  tcase_add_test(tc, sscanf_spec_hd_14);
  tcase_add_test(tc, sscanf_spec_hd_15);
  tcase_add_test(tc, sscanf_spec_hd_16);
  tcase_add_test(tc, sscanf_spec_hd_17);
  tcase_add_test(tc, sscanf_spec_hd_18);
  tcase_add_test(tc, sscanf_spec_hd_19);
  tcase_add_test(tc, sscanf_spec_hd_20);
  tcase_add_test(tc, sscanf_spec_hd_21);
  tcase_add_test(tc, sscanf_spec_hd_22);
  tcase_add_test(tc, sscanf_spec_hd_23);
  tcase_add_test(tc, sscanf_spec_hd_24);
  tcase_add_test(tc, sscanf_spec_hd_25);

  tcase_add_test(tc, sscanf_spec_d_1);
  tcase_add_test(tc, sscanf_spec_d_2);
  tcase_add_test(tc, sscanf_spec_d_3);
  tcase_add_test(tc, sscanf_spec_d_4);
  tcase_add_test(tc, sscanf_spec_d_5);
  tcase_add_test(tc, sscanf_spec_d_6);
  tcase_add_test(tc, sscanf_spec_d_7);
  tcase_add_test(tc, sscanf_spec_d_8);
  tcase_add_test(tc, sscanf_spec_d_9);
  tcase_add_test(tc, sscanf_spec_d_10);
  tcase_add_test(tc, sscanf_spec_d_11);
  tcase_add_test(tc, sscanf_spec_d_12);
  tcase_add_test(tc, sscanf_spec_d_13);
  tcase_add_test(tc, sscanf_spec_d_14);
  tcase_add_test(tc, sscanf_spec_d_15);
  tcase_add_test(tc, sscanf_spec_d_16);
  tcase_add_test(tc, sscanf_spec_d_17);
  tcase_add_test(tc, sscanf_spec_d_18);
  tcase_add_test(tc, sscanf_spec_d_19);
  tcase_add_test(tc, sscanf_spec_d_20);
  tcase_add_test(tc, sscanf_spec_d_21);
  tcase_add_test(tc, sscanf_spec_d_22);
  tcase_add_test(tc, sscanf_spec_d_23);
  tcase_add_test(tc, sscanf_spec_d_24);
  tcase_add_test(tc, sscanf_spec_d_25);

  tcase_add_test(tc, sscanf_spec_ld_1);
  tcase_add_test(tc, sscanf_spec_ld_2);
  tcase_add_test(tc, sscanf_spec_ld_3);
  tcase_add_test(tc, sscanf_spec_ld_4);
  tcase_add_test(tc, sscanf_spec_ld_5);
  tcase_add_test(tc, sscanf_spec_ld_6);
  tcase_add_test(tc, sscanf_spec_ld_7);
  tcase_add_test(tc, sscanf_spec_ld_8);
  tcase_add_test(tc, sscanf_spec_ld_9);
  tcase_add_test(tc, sscanf_spec_ld_10);
  tcase_add_test(tc, sscanf_spec_ld_11);
  tcase_add_test(tc, sscanf_spec_ld_12);
  tcase_add_test(tc, sscanf_spec_ld_13);
  tcase_add_test(tc, sscanf_spec_ld_14);
  tcase_add_test(tc, sscanf_spec_ld_15);
  tcase_add_test(tc, sscanf_spec_ld_16);
  tcase_add_test(tc, sscanf_spec_ld_17);
  tcase_add_test(tc, sscanf_spec_ld_18);
  tcase_add_test(tc, sscanf_spec_ld_19);
  tcase_add_test(tc, sscanf_spec_ld_20);
  tcase_add_test(tc, sscanf_spec_ld_21);
  tcase_add_test(tc, sscanf_spec_ld_22);
  tcase_add_test(tc, sscanf_spec_ld_23);
  tcase_add_test(tc, sscanf_spec_ld_24);
  tcase_add_test(tc, sscanf_spec_ld_25);

  tcase_add_test(tc, sscanf_spec_lld_1);
  tcase_add_test(tc, sscanf_spec_lld_2);
  tcase_add_test(tc, sscanf_spec_lld_3);
  tcase_add_test(tc, sscanf_spec_lld_4);
  tcase_add_test(tc, sscanf_spec_lld_5);
  tcase_add_test(tc, sscanf_spec_lld_6);
  tcase_add_test(tc, sscanf_spec_lld_7);
  tcase_add_test(tc, sscanf_spec_lld_8);
  tcase_add_test(tc, sscanf_spec_lld_9);
  tcase_add_test(tc, sscanf_spec_lld_10);
  tcase_add_test(tc, sscanf_spec_lld_11);
  tcase_add_test(tc, sscanf_spec_lld_12);
  tcase_add_test(tc, sscanf_spec_lld_13);
  tcase_add_test(tc, sscanf_spec_lld_14);
  tcase_add_test(tc, sscanf_spec_lld_15);
  tcase_add_test(tc, sscanf_spec_lld_16);
  tcase_add_test(tc, sscanf_spec_lld_17);
  tcase_add_test(tc, sscanf_spec_lld_18);
  tcase_add_test(tc, sscanf_spec_lld_19);
  tcase_add_test(tc, sscanf_spec_lld_20);
  tcase_add_test(tc, sscanf_spec_lld_21);
  tcase_add_test(tc, sscanf_spec_lld_22);
  tcase_add_test(tc, sscanf_spec_lld_23);
  tcase_add_test(tc, sscanf_spec_lld_24);
  tcase_add_test(tc, sscanf_spec_lld_25);

  suite_add_tcase(s, tc);

  return s;
}

Suite *test_sscanf_x(void) {
  Suite *s = suite_create("S21_SSCANF_X");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_hhx_1);
  tcase_add_test(tc, sscanf_spec_hhx_2);
  tcase_add_test(tc, sscanf_spec_hhx_3);
  tcase_add_test(tc, sscanf_spec_hhx_4);
  tcase_add_test(tc, sscanf_spec_hhx_5);
  tcase_add_test(tc, sscanf_spec_hhx_6);
  tcase_add_test(tc, sscanf_spec_hhx_7);
  tcase_add_test(tc, sscanf_spec_hhx_8);
  tcase_add_test(tc, sscanf_spec_hhx_9);
  tcase_add_test(tc, sscanf_spec_hhx_10);
  tcase_add_test(tc, sscanf_spec_hhx_11);
  tcase_add_test(tc, sscanf_spec_hx_1);
  tcase_add_test(tc, sscanf_spec_hx_2);
  tcase_add_test(tc, sscanf_spec_hx_3);
  tcase_add_test(tc, sscanf_spec_hx_4);
  tcase_add_test(tc, sscanf_spec_hx_5);
  tcase_add_test(tc, sscanf_spec_hx_6);
  tcase_add_test(tc, sscanf_spec_hx_7);
  tcase_add_test(tc, sscanf_spec_hx_8);
  tcase_add_test(tc, sscanf_spec_hx_9);
  tcase_add_test(tc, sscanf_spec_hx_10);
  tcase_add_test(tc, sscanf_spec_hx_11);
  tcase_add_test(tc, sscanf_spec_x_1);
  tcase_add_test(tc, sscanf_spec_x_2);
  tcase_add_test(tc, sscanf_spec_x_3);
  tcase_add_test(tc, sscanf_spec_x_4);
  tcase_add_test(tc, sscanf_spec_x_5);
  tcase_add_test(tc, sscanf_spec_x_6);
  tcase_add_test(tc, sscanf_spec_x_7);
  tcase_add_test(tc, sscanf_spec_x_8);
  tcase_add_test(tc, sscanf_spec_x_9);
  tcase_add_test(tc, sscanf_spec_x_10);
  tcase_add_test(tc, sscanf_spec_x_11);
  tcase_add_test(tc, sscanf_spec_lx_1);
  tcase_add_test(tc, sscanf_spec_lx_2);
  tcase_add_test(tc, sscanf_spec_lx_3);
  tcase_add_test(tc, sscanf_spec_lx_4);
  tcase_add_test(tc, sscanf_spec_lx_5);
  tcase_add_test(tc, sscanf_spec_lx_6);
  tcase_add_test(tc, sscanf_spec_lx_7);
  tcase_add_test(tc, sscanf_spec_lx_8);
  tcase_add_test(tc, sscanf_spec_lx_9);
  tcase_add_test(tc, sscanf_spec_lx_10);
  tcase_add_test(tc, sscanf_spec_lx_11);
  tcase_add_test(tc, sscanf_spec_llx_1);
  tcase_add_test(tc, sscanf_spec_llx_2);
  tcase_add_test(tc, sscanf_spec_llx_3);
  tcase_add_test(tc, sscanf_spec_llx_4);
  tcase_add_test(tc, sscanf_spec_llx_5);
  tcase_add_test(tc, sscanf_spec_llx_6);
  tcase_add_test(tc, sscanf_spec_llx_7);
  tcase_add_test(tc, sscanf_spec_llx_8);
  tcase_add_test(tc, sscanf_spec_llx_9);
  tcase_add_test(tc, sscanf_spec_llx_10);
  tcase_add_test(tc, sscanf_spec_llx_11);

  suite_add_tcase(s, tc);
  return s;
}

Suite *test_sscanf_real(void) {
  Suite *s = suite_create("S21 SSCANF F");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_f_1);
  tcase_add_test(tc, sscanf_spec_f_2);
  tcase_add_test(tc, sscanf_spec_f_3);
  tcase_add_test(tc, sscanf_spec_f_4);
  tcase_add_test(tc, sscanf_spec_f_5);
  tcase_add_test(tc, sscanf_spec_f_6);
  tcase_add_test(tc, sscanf_spec_f_7);
  tcase_add_test(tc, sscanf_spec_f_8);
  tcase_add_test(tc, sscanf_spec_f_9);
  tcase_add_test(tc, sscanf_spec_f_10);
  tcase_add_test(tc, sscanf_spec_f_11);
  tcase_add_test(tc, sscanf_spec_f_12);
  tcase_add_test(tc, sscanf_spec_f_13);
  tcase_add_test(tc, sscanf_spec_f_14);
  tcase_add_test(tc, sscanf_spec_f_15);
  tcase_add_test(tc, sscanf_spec_f_18);
  tcase_add_test(tc, sscanf_spec_f_19);
  tcase_add_test(tc, test_11_sscanf);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_sscanf_p(void) {
  Suite *s = suite_create("S21 SSCANF P");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_p_1);
  tcase_add_test(tc, sscanf_spec_p_2);
  tcase_add_test(tc, sscanf_spec_p_3);
  tcase_add_test(tc, sscanf_spec_p_4);
  tcase_add_test(tc, sscanf_spec_p_5);
  tcase_add_test(tc, sscanf_spec_p_6);
  tcase_add_test(tc, sscanf_spec_p_7);
  tcase_add_test(tc, sscanf_spec_p_8);
  tcase_add_test(tc, sscanf_spec_p_9);
  tcase_add_test(tc, sscanf_spec_p_10);
  tcase_add_test(tc, sscanf_spec_p_11);
  tcase_add_test(tc, sscanf_spec_p_12);
  tcase_add_test(tc, sscanf_spec_p_13);
  tcase_add_test(tc, sscanf_spec_p_14);
  tcase_add_test(tc, sscanf_spec_p_15);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_sscanf_o(void) {
  Suite *s = suite_create("S21 SSCANF O");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_hho_1);
  tcase_add_test(tc, sscanf_spec_hho_2);
  tcase_add_test(tc, sscanf_spec_hho_3);
  tcase_add_test(tc, sscanf_spec_hho_4);
  tcase_add_test(tc, sscanf_spec_hho_5);
  tcase_add_test(tc, sscanf_spec_hho_6);
  tcase_add_test(tc, sscanf_spec_ho_1);
  tcase_add_test(tc, sscanf_spec_ho_2);
  tcase_add_test(tc, sscanf_spec_ho_3);
  tcase_add_test(tc, sscanf_spec_ho_4);
  tcase_add_test(tc, sscanf_spec_ho_5);
  tcase_add_test(tc, sscanf_spec_ho_6);
  tcase_add_test(tc, sscanf_spec_o_1);
  tcase_add_test(tc, sscanf_spec_o_2);
  tcase_add_test(tc, sscanf_spec_o_3);
  tcase_add_test(tc, sscanf_spec_o_4);
  tcase_add_test(tc, sscanf_spec_o_5);
  tcase_add_test(tc, sscanf_spec_o_6);
  tcase_add_test(tc, sscanf_spec_lo_1);
  tcase_add_test(tc, sscanf_spec_lo_2);
  tcase_add_test(tc, sscanf_spec_lo_3);
  tcase_add_test(tc, sscanf_spec_lo_4);
  tcase_add_test(tc, sscanf_spec_lo_5);
  tcase_add_test(tc, sscanf_spec_lo_6);
  tcase_add_test(tc, sscanf_spec_llo_1);
  tcase_add_test(tc, sscanf_spec_llo_2);
  tcase_add_test(tc, sscanf_spec_llo_3);
  tcase_add_test(tc, sscanf_spec_llo_4);
  tcase_add_test(tc, sscanf_spec_llo_5);
  tcase_add_test(tc, sscanf_spec_llo_6);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_sscanf_n(void) {
  Suite *s = suite_create("S21 SSCANF N");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_n_1);
  tcase_add_test(tc, sscanf_spec_n_2);
  tcase_add_test(tc, sscanf_spec_n_3);
  tcase_add_test(tc, sscanf_spec_n_4);
  tcase_add_test(tc, sscanf_spec_n_5);
  tcase_add_test(tc, sscanf_spec_n_6);
  tcase_add_test(tc, sscanf_spec_n_7);
  tcase_add_test(tc, sscanf_spec_n_8);
  tcase_add_test(tc, sscanf_spec_n_9);
  tcase_add_test(tc, sscanf_spec_n_10);

  suite_add_tcase(s, tc);
  return s;
}

Suite *test_sscanf_i(void) {
  Suite *s = suite_create("S21 SSCANF I");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_i_dec_1);
  tcase_add_test(tc, sscanf_spec_i_dec_2);
  tcase_add_test(tc, sscanf_spec_i_dec_3);
  tcase_add_test(tc, sscanf_spec_i_dec_4);
  tcase_add_test(tc, sscanf_spec_i_dec_5);
  tcase_add_test(tc, sscanf_spec_i_dec_6);
  tcase_add_test(tc, sscanf_spec_i_dec_7);
  tcase_add_test(tc, sscanf_spec_i_dec_8);

  tcase_add_test(tc, sscanf_spec_i_oct_1);
  tcase_add_test(tc, sscanf_spec_i_oct_6);
  tcase_add_test(tc, sscanf_spec_i_oct_7);
  tcase_add_test(tc, sscanf_spec_i_oct_8);

  tcase_add_test(tc, sscanf_spec_i_hex_1);
  tcase_add_test(tc, sscanf_spec_i_hex_6);
  tcase_add_test(tc, sscanf_spec_i_hex_7);
  tcase_add_test(tc, sscanf_spec_i_hex_8);

  tcase_add_test(tc, sscanf_spec_hi_dec_1);
  tcase_add_test(tc, sscanf_spec_hi_dec_6);
  tcase_add_test(tc, sscanf_spec_hi_dec_7);
  tcase_add_test(tc, sscanf_spec_hi_dec_8);

  tcase_add_test(tc, sscanf_spec_hi_oct_1);
  tcase_add_test(tc, sscanf_spec_hi_oct_6);
  tcase_add_test(tc, sscanf_spec_hi_oct_7);
  tcase_add_test(tc, sscanf_spec_hi_oct_8);

  tcase_add_test(tc, sscanf_spec_hi_hex_1);
  tcase_add_test(tc, sscanf_spec_hi_hex_6);
  tcase_add_test(tc, sscanf_spec_hi_hex_7);
  tcase_add_test(tc, sscanf_spec_hi_hex_8);

  tcase_add_test(tc, sscanf_spec_li_dec_1);
  tcase_add_test(tc, sscanf_spec_li_dec_6);
  tcase_add_test(tc, sscanf_spec_li_dec_7);
  tcase_add_test(tc, sscanf_spec_li_dec_8);

  tcase_add_test(tc, sscanf_spec_li_oct_1);
  tcase_add_test(tc, sscanf_spec_li_oct_6);
  tcase_add_test(tc, sscanf_spec_li_oct_7);
  tcase_add_test(tc, sscanf_spec_li_oct_8);

  tcase_add_test(tc, sscanf_spec_li_hex_1);
  tcase_add_test(tc, sscanf_spec_li_hex_6);
  tcase_add_test(tc, sscanf_spec_li_hex_7);

  suite_add_tcase(s, tc);
  return s;
}

Suite *test_sscanf_empty(void) {
  Suite *s = suite_create("S21 SSCANF EMPTY");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_empty_1);
  tcase_add_test(tc, sscanf_empty_2);
  tcase_add_test(tc, sscanf_empty_3);
  tcase_add_test(tc, sscanf_empty_5);
  tcase_add_test(tc, sscanf_empty_6);
  tcase_add_test(tc, sscanf_empty_7);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_sscanf_c(void) {
  Suite *s = suite_create("S21 SSCANF C");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_c_2);
  tcase_add_test(tc, sscanf_spec_c_4);
  tcase_add_test(tc, sscanf_spec_c_5);
  tcase_add_test(tc, sscanf_spec_c_6);
  tcase_add_test(tc, sscanf_spec_c_7);
  tcase_add_test(tc, sscanf_spec_c_8);
  suite_add_tcase(s, tc);
  return s;
}
Suite *test_sscanf_s(void) {
  Suite *s = suite_create("S21 SSCANF S");
  TCase *tc = tcase_create("sscanf_tc");
  tcase_add_test(tc, sscanf_spec_s_1);
  tcase_add_test(tc, sscanf_spec_s_2);
  tcase_add_test(tc, sscanf_spec_s_3);
  tcase_add_test(tc, sscanf_spec_s_4);
  tcase_add_test(tc, sscanf_spec_s_5);
  suite_add_tcase(s, tc);
  return s;
}

void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main(void) {
  int fail = 0;
  case_test(test_sscanf_empty(), &fail);
  case_test(test_sscanf_c(), &fail);
  case_test(test_sscanf_s(), &fail);
  case_test(test_sscanf_i(), &fail);
  case_test(test_sscanf_o(), &fail);
  case_test(test_sscanf_x(), &fail);
  case_test(test_sscanf_p(), &fail);
  case_test(test_sscanf_real(), &fail);
  case_test(test_sscanf_d(), &fail);
  case_test(test_sscanf_n(), &fail);

  printf("========= FAILED: %d =========\n", fail);

  return fail;
}
