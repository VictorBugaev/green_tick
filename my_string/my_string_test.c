#include "my_string.h"

#include <check.h>
#include <string.h>

// memchr tests

START_TEST(my_memchr_cmp) {
  char str[16] = "Hello World";
  int c = 'o';
  my_size_t n = my_strlen(str);
  ck_assert_str_eq(my_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(my_memchr_no_cmp) {
  char str[16] = "Hello World";
  int c = 'a';
  my_size_t n = my_strlen(str);
  ck_assert_pstr_eq(my_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(my_memchr_str_less_n) {
  char str[16] = "I'm tired";
  int c = 'd';
  my_size_t n = my_strlen(str) + 4;
  ck_assert_str_eq(my_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(my_memchr_str_empty) {
  char str[2] = "";
  int c = 'p';
  my_size_t n = my_strlen(str);
  ck_assert_pstr_eq(my_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(my_memchr_c_null) {
  char str[16] = "65tfhdf";
  int c = '\0';
  my_size_t n = my_strlen(str);
  ck_assert_pstr_eq(my_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(my_memchr_c_less_Zero) {
  char str[16] = "65tfhdf";
  int c = -6;
  my_size_t n = my_strlen(str);
  ck_assert_pstr_eq(my_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(my_memchr_n_eq_Zero) {
  char str[16] = "65tfhdf";
  int c = 't';
  my_size_t n = 0;
  ck_assert_pstr_eq(my_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(my_memchr_str_null) {
  char *str = my_NULL;
  int c = 't';
  my_size_t n = 0;
  ck_assert_ptr_null(my_memchr(str, c, n));
}
END_TEST

// memcmp tests

START_TEST(my_memcmp_part_cmp) {
  char str_1[5][16] = {"65tfhdf", "ajhesdtjf", "8273tq", "auerta", "u237tr"};
  char str_2[5][16] = {"65tfbvh", "ajhesdtgf", "8273aw", "auertp", "u2-7tr"};
  for (int i = 0; i < 5; i++) {
    my_size_t n = my_strlen(str_1[i]);
    int res_1 = my_memcmp(str_1[i], str_2[i], n);
    int res_2 = memcmp(str_1[i], str_2[i], n);
    ck_assert_int_eq(res_1, res_2);
  }
}
END_TEST

START_TEST(my_memcmp_len_less_n) {
  char str_1[16] = "aksudfd";
  char str_2[16] = "df";
  my_size_t n = my_strlen(str_1) + 4;
  int res_1 = my_memcmp(str_1, str_2, n);
  int res_2 = memcmp(str_1, str_2, n);
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(my_memcmp_n_eq_zero) {
  char str_1[16] = "asd45;wr";
  char str_2[16] = ":wr";
  my_size_t n = 0;
  ck_assert_int_eq(my_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(my_memcmp_str1_null) {
  char *str_1 = "";
  char str_2[16] = ":wr";
  my_size_t n = 2;
  int res_1 = my_memcmp(str_1, str_2, n);
  int res_2 = memcmp(str_1, str_2, n);
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(my_memcmp_str2_null) {
  char str_1[16] = "aksfaaf";
  char *str_2 = "";
  my_size_t n = my_strlen(str_1);
  int res_1 = my_memcmp(str_1, str_2, n);
  int res_2 = memcmp(str_1, str_2, n);
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(my_memcmp_full_cmp) {
  char str_1[16] = "memcmp test";
  char str_2[16] = "memcmp test";
  my_size_t n = my_strlen(str_1);
  ck_assert_int_eq(my_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(my_memcmp_no_cmp) {
  char str_1[16] = "memcmp test";
  char str_2[16] = ";<w";
  my_size_t n = my_strlen(str_1);
  int res_1 = my_memcmp(str_1, str_2, n);
  int res_2 = memcmp(str_1, str_2, n);
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

// memcpy tests

START_TEST(my_memcpy_default) {
  char dest_1[16] = "";
  char dest_2[16] = "";
  char src[5][16] = {"memcpy test", "some text", "adfaw45", "aijfa o",
                     "1q024578"};
  for (int i = 0; i < 5; i++) {
    my_size_t n = my_strlen(src[i]);
    my_memcpy(dest_1, src[i], n);
    memcpy(dest_2, src[i], n);
    ck_assert_str_eq(dest_1, dest_2);
    dest_1[0] = '\0';
    dest_2[0] = '\0';
  }
}
END_TEST

START_TEST(my_memcpy_dest_not_empty) {
  char dest_1[16] = "ahsdgf";
  char dest_2[16] = "ahsdgf";
  char src[16] = "trulyalya";
  my_size_t n = my_strlen(src);
  my_memcpy(dest_1, src, n);
  memcpy(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(my_memcpy_src_empty) {
  char dest_1[16] = "zsdfasd";
  char dest_2[16] = "zsdfasd";
  char src[16] = "";
  my_size_t n = my_strlen(src);
  my_memcpy(dest_1, src, n);
  memcpy(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(my_memcpy_n_eq_zero) {
  char dest_1[16] = "ashdf";
  char dest_2[16] = "ashdf";
  char src[16] = "jhagsdf";
  my_size_t n = 0;
  my_memcpy(dest_1, src, n);
  memcpy(dest_2, src, n);
  ck_assert_pstr_eq(dest_1, dest_2);
}
END_TEST

// memset tests

START_TEST(my_memset_default) {
  char str_1[5][16] = {"ajsdhf", "1 23f ", "`9  283yjaf", "+*/++", "8Q oi"};
  char str_2[5][16] = {"ajsdhf", "1 23f ", "`9  283yjaf", "+*/++", "8Q oi"};
  int c = 56;
  for (int i = 0; i < 5; i++) {
    my_size_t n = my_strlen(str_1[i]) - 3;
    my_memset(str_1[i], c, n);
    memset(str_2[i], c, n);
    ck_assert_str_eq(str_1[i], str_2[i]);
  }
}
END_TEST

START_TEST(my_memset_NULL) {
  char *str_1 = my_NULL;
  char *str_2 = my_NULL;
  int c = 56;
  my_size_t n = 0;
  my_memset(str_1, c, n);
  memset(str_2, c, n);
  ck_assert_pstr_eq(str_1, str_2);
}
END_TEST

START_TEST(my_memset_n_zero) {
  char str_1[16] = "my_NULL";
  char str_2[16] = "my_NULL";
  int c = 56;
  my_size_t n = 0;
  my_memset(str_1, c, n);
  memset(str_2, c, n);
  ck_assert_str_eq(str_1, str_2);
}
END_TEST

START_TEST(my_memset_c_less_zero) {
  char str_1[16] = "trulala";
  char str_2[16] = "trulala";
  int c = -56;
  my_size_t n = 2;
  my_memset(str_1, c, n);
  memset(str_2, c, n);
  ck_assert_str_eq(str_1, str_2);
}
END_TEST

START_TEST(my_memset_str_empty) {
  char str_1[16] = "\0";
  char str_2[16] = "\0";
  int c = 56;
  my_size_t n = 13;
  my_memset(str_1, c, n);
  memset(str_2, c, n);
  ck_assert_str_eq(str_1, str_2);
}
END_TEST

// strncat tests

START_TEST(my_strncat_default) {
  char dest_1[5][16] = {"ajsdhf", "1 23f ", "`9  283yjaf", "+*/++", "8Q oi"};
  char dest_2[5][16] = {"ajsdhf", "1 23f ", "`9  283yjaf", "+*/++", "8Q oi"};
  char src[5][16] = {"yawgfe", "1o824", " iuraf", "5465", "13qou74r"};
  for (int i = 0; i < 5; i++) {
    my_size_t n = my_strlen(src[i]);
    my_strncat(dest_1[i], src[i], n);
    strncat(dest_2[i], src[i], n);
    ck_assert_str_eq(dest_1[i], dest_2[i]);
  }
}
END_TEST

START_TEST(my_strncat_len_less_dest) {
  char dest_1[32] = "asdfasdf";
  char dest_2[32] = "asdfasdf";
  char src[16] = "nqurt";
  my_size_t n = my_strlen(src) - 2;
  my_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(my_strncat_dest_less_len) {
  char dest_1[20] = "aiuey que";
  char dest_2[20] = "aiuey que";
  char src[16] = "98ahgoladhuhdk";
  my_size_t n = my_strlen(src);
  my_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(my_strncat_empty_dest) {
  char dest_1[16] = "";
  char dest_2[16] = "";
  char src[16] = "nqurt";
  my_size_t n = my_strlen(src);
  my_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(my_strncat_empty_src) {
  char dest_1[16] = "ASiausdyf";
  char dest_2[16] = "ASiausdyf";
  char src[16] = "\0";
  my_size_t n = my_strlen(src);
  my_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(my_strncat_all_empty) {
  char dest_1[16] = "\0";
  char dest_2[16] = "\0";
  char src[16] = "\0";
  my_size_t n = my_strlen(src);
  my_strncat(dest_1, src, n);
  strncat(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

// strchr test

START_TEST(my_strchr_cmp) {
  char array_str[5][10] = {"qwertxews", "rtukuytf", "cbhnhhy", "ahgubvx",
                           "tuhgdh"};
  int array_symb[5] = {'w', 'r', 'h', 'x', 'u'};
  for (int i = 0; i < 5; i++)
    ck_assert_str_eq(my_strchr(array_str[i], array_symb[i]),
                     strchr(array_str[i], array_symb[i]));
}
END_TEST

START_TEST(my_strchr_no_cmp) {
  char *str = "z86hs-vbcx";
  int symb = 'o';
  ck_assert_pstr_eq(my_strchr(str, symb), strchr(str, symb));
}
END_TEST

START_TEST(my_strchr_less_zero) {
  char *str = "kuyuteasd";
  int symb = -1;
  ck_assert_pstr_eq(my_strchr(str, symb), strchr(str, symb));
}
END_TEST

START_TEST(my_strchr_null_symb) {
  char *str = "Hello World";
  int symb = '\0';
  ck_assert_pstr_eq(my_strchr(str, symb), strchr(str, symb));
}
END_TEST

START_TEST(my_strchr_empty_str) {
  char *str = "";
  int symb = 'a';
  ck_assert_pstr_eq(my_strchr(str, symb), strchr(str, symb));
}
END_TEST

START_TEST(my_strchr_empty_str_symb) {
  char *str = "";
  int symb = '\0';
  ck_assert_pstr_eq(my_strchr(str, symb), strchr(str, symb));
}
END_TEST

// strncmp test

START_TEST(my_strncmp_part_cmp) {
  char str_1[5][16] = {"65tfhdf", "ajhesdtjf", "8273tq", "auerta", "u237tr"};
  char str_2[5][16] = {"65tfbvh", "ajhesdtgf", "8273aw", "auertp", "u2-7tr"};
  for (int i = 0; i < 5; i++) {
    my_size_t n = my_strlen(str_1[i]);
    int res_1 = my_strncmp(str_1[i], str_2[i], n);
    int res_2 = strncmp(str_1[i], str_2[i], n);
    ck_assert_int_eq(res_1, res_2);
  }
}
END_TEST

START_TEST(my_strncmp_len_less_n) {
  char str_1[16] = "aksudfd";
  char str_2[16] = "df";
  my_size_t n = my_strlen(str_1) + 4;
  int res_1 = my_strncmp(str_1, str_2, n);
  int res_2 = strncmp(str_1, str_2, n);
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(my_strncmp_n_eq_zero) {
  char str_1[16] = "asd45;wr";
  char str_2[16] = ":wr";
  my_size_t n = 0;
  ck_assert_int_eq(my_strncmp(str_1, str_2, n), strncmp(str_1, str_2, n));
}
END_TEST

START_TEST(my_strncmp_str1_null) {
  char *str_1 = "";
  char str_2[16] = ":wr";
  my_size_t n = 2;
  int res_1 = my_strncmp(str_1, str_2, n);
  int res_2 = strncmp(str_1, str_2, n);
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(my_strncmp_str2_null) {
  char str_1[16] = "aksfaaf";
  char *str_2 = "";
  my_size_t n = my_strlen(str_1);
  int res_1 = my_strncmp(str_1, str_2, n);
  int res_2 = strncmp(str_1, str_2, n);
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

START_TEST(my_strncmp_full_cmp) {
  char str_1[16] = "strncmp test";
  char str_2[16] = "strncmp test";
  my_size_t n = my_strlen(str_1);
  ck_assert_int_eq(my_strncmp(str_1, str_2, n), strncmp(str_1, str_2, n));
}
END_TEST

START_TEST(my_strncmp_no_cmp) {
  char str_1[16] = "strncmp test";
  char str_2[16] = ";<w";
  my_size_t n = my_strlen(str_1);
  int res_1 = my_strncmp(str_1, str_2, n);
  int res_2 = strncmp(str_1, str_2, n);
  ck_assert_int_eq(res_1, res_2);
}
END_TEST

// strncpy test

START_TEST(my_strncpy_default) {
  char dest_1[16] = "";
  char dest_2[16] = "";
  char src[5][16] = {"strncpy test", "some text", "adfaw45", "aijfa o",
                     "1q024578"};
  for (int i = 0; i < 5; i++) {
    my_size_t n = my_strlen(src[i]);
    my_strncpy(dest_1, src[i], n);
    strncpy(dest_2, src[i], n);
    ck_assert_str_eq(dest_1, dest_2);
    dest_1[0] = '\0';
    dest_2[0] = '\0';
  }
}
END_TEST

START_TEST(my_strncpy_dest_not_empty) {
  char dest_1[16] = "ahsdgf";
  char dest_2[16] = "ahsdgf";
  char src[16] = "trulyalya";
  my_size_t n = my_strlen(src);
  my_strncpy(dest_1, src, n);
  strncpy(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(my_strncpy_src_empty) {
  char dest_1[16] = "zsdfasd";
  char dest_2[16] = "zsdfasd";
  char src[16] = "";
  my_size_t n = my_strlen(src);
  my_strncpy(dest_1, src, n);
  strncpy(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}
END_TEST

START_TEST(my_strncpy_n_eq_zero) {
  char dest_1[16] = "ashdf";
  char dest_2[16] = "ashdf";
  char src[16] = "jhagsdf";
  my_size_t n = 0;
  my_strncpy(dest_1, src, n);
  strncpy(dest_2, src, n);
  ck_assert_pstr_eq(dest_1, dest_2);
}
END_TEST
START_TEST(my_strncpy_src_shorter) {
  char dest_1[16] = "ahsdgsdafgf";
  char dest_2[16] = "ahsdgsdafgf";
  char src[4] = "tro\0";
  my_size_t n = my_strlen(dest_1);
  my_strncpy(dest_1, src, n);
  strncpy(dest_2, src, n);
  ck_assert_str_eq(dest_1, dest_2);
}

// strcspn tests

START_TEST(my_strcspn_match) {
  char array_str_1[5][10] = {"123456781", "fhs74iud", "hhhhh", "siu34 x",
                             "t3q45h"};
  char array_str_2[5][5] = {"34", "ud", "hh", " x", "t3"};
  for (int i = 0; i < 5; i++)
    ck_assert_int_eq(my_strcspn(array_str_1[i], array_str_2[i]),
                     strcspn(array_str_1[i], array_str_2[i]));
}
END_TEST

START_TEST(my_strcspn_no_match) {
  char str_1[12] = "sf2q345dusf";
  char str_2[3] = "31";
  ck_assert_int_eq(my_strcspn(str_1, str_2), strcspn(str_1, str_2));
}
END_TEST

START_TEST(my_strcspn_str_2_empty) {
  char str_1[9] = "k3245asd";
  char *str_2 = "\0";
  ck_assert_int_eq(my_strcspn(str_1, str_2), strcspn(str_1, str_2));
}
END_TEST

START_TEST(my_strcspn_str_1_empty) {
  char str_1[9] = "";
  char str_2[4] = ";5s";
  ck_assert_int_eq(my_strcspn(str_1, str_2), strcspn(str_1, str_2));
}
END_TEST

START_TEST(my_strcspn_str_1_str_2_empty) {
  char str_1[4] = "";
  char str_2[4] = "\0";
  ck_assert_int_eq(my_strcspn(str_1, str_2), strcspn(str_1, str_2));
}
END_TEST

// strerror tests

START_TEST(my_strerror_test) {
  for (int i = -5; i < 150; i++) ck_assert_str_eq(my_strerror(i), strerror(i));
}
END_TEST

START_TEST(my_strerror_long_int_pos) {
  int num_3 = 2147483647;
  ck_assert_str_eq(strerror(num_3), my_strerror(num_3));
}
END_TEST

START_TEST(my_strerror_long_int_neg) {
  int num_4 = -2147483647;
  ck_assert_str_eq(strerror(num_4), my_strerror(num_4));
}
END_TEST

// strlen tests

START_TEST(my_strlen_default) {
  char array_str[5][10] = {"qwertxews", "rtukuytf", "cbhnhhy", "ahgubvx",
                           "tuhgdh"};
  for (int i = 0; i < 5; i++)
    ck_assert_int_eq(my_strlen(array_str[i]), strlen(array_str[i]));
}
END_TEST

START_TEST(my_strlen_null) {
  char *str = "\0";
  ck_assert_int_eq(my_strlen(str), strlen(str));
}
END_TEST

// strpbrk tests

START_TEST(my_strpbrk_match) {
  char array_str1[5][10] = {"123456781", "fhs74iud", "hhhhh", "siu34 x",
                            "t3q45h"};
  char array_str2[5][5] = {"34", "ud", "hh", " x", "t3"};
  for (int i = 0; i < 5; i++)
    ck_assert_str_eq(my_strpbrk(array_str1[i], array_str2[i]),
                     strpbrk(array_str1[i], array_str2[i]));
}
END_TEST

START_TEST(my_strpbrk_no_match) {
  char str1[12] = "sf2q345dusf";
  char str2[3] = "31";
  ck_assert_pstr_eq(my_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(my_strpbrk_str2_empty) {
  char str1[9] = "k3245asd";
  char *str2 = "\0";
  ck_assert_pstr_eq(my_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(my_strpbrk_str1_empty) {
  char str1[9] = "";
  char str2[4] = ";5s";
  ck_assert_pstr_eq(my_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(my_strpbrk_str1_str2_empty) {
  char str1[4] = "";
  char str2[4] = "\0";
  ck_assert_pstr_eq(my_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// strrchr tests

START_TEST(my_strrchr_cmp) {
  char array_str[5][10] = {"qwertxews", "rtukuytf", "cbhnhhy", "ahgubvx",
                           "tuhgdh"};
  int array_symb[5] = {'w', 'r', 'h', 'x', 'u'};
  for (int i = 0; i < 5; i++)
    ck_assert_str_eq(my_strrchr(array_str[i], array_symb[i]),
                     strrchr(array_str[i], array_symb[i]));
}
END_TEST

START_TEST(my_strrchr_no_cmp) {
  char *str = "z86hs-vbcx";
  int symb = 'o';
  ck_assert_pstr_eq(my_strrchr(str, symb), strrchr(str, symb));
}
END_TEST

START_TEST(my_strrchr_less_zero) {
  char *str = "kuyuteasd";
  int symb = -100;
  ck_assert_pstr_eq(my_strrchr(str, symb), strrchr(str, symb));
}
END_TEST

START_TEST(my_strrchr_null_symb) {
  char *str = "Hello World";
  int symb = '\0';
  ck_assert_pstr_eq(my_strrchr(str, symb), strrchr(str, symb));
}
END_TEST

START_TEST(my_strrchr_empty_str) {
  char *str = "";
  int symb = 'a';
  ck_assert_pstr_eq(my_strrchr(str, symb), strrchr(str, symb));
}
END_TEST

START_TEST(my_strrchr_empty_str_symb) {
  char *str = "";
  int symb = '\0';
  ck_assert_pstr_eq(my_strrchr(str, symb), strrchr(str, symb));
}
END_TEST

// strstr tests
START_TEST(my_strstr_match) {
  char array_haystack[5][10] = {"123456781", "fhs74iud", "hhhhh", "siu34 x",
                                "t3q45h"};
  char array_needle[5][5] = {"34", "ud", "hh", " x", "t3"};
  for (int i = 0; i < 5; i++)
    ck_assert_str_eq(my_strstr(array_haystack[i], array_needle[i]),
                     strstr(array_haystack[i], array_needle[i]));
}
END_TEST

START_TEST(my_strstr_no_match) {
  char haystack[12] = "sf2q345dusf";
  char needle[3] = "31";
  ck_assert_pstr_eq(my_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(my_strstr_needle_empty) {
  char haystack[9] = "k3245asd";
  char *needle = "\0";
  ck_assert_str_eq(my_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(my_strstr_haystack_empty) {
  char haystack[9] = "";
  char needle[4] = ";5s";
  ck_assert_pstr_eq(my_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(my_strstr_haystack_needle_empty) {
  char haystack[4] = "";
  char needle[4] = "\0";
  ck_assert_str_eq(my_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// strtok tests

START_TEST(my_strtok_match) {
  char str_1[32] = "test1/test2/test3/test4";
  char str_2[32] = "test1/test2/test3/test4";
  char delim[4] = "/,";
  ck_assert_str_eq(my_strtok(str_1, delim), strtok(str_2, delim));
  ck_assert_str_eq(my_strtok(my_NULL, delim), strtok(my_NULL, delim));
  ck_assert_str_eq(my_strtok(my_NULL, delim), strtok(my_NULL, delim));
  ck_assert_str_eq(my_strtok(my_NULL, delim), strtok(my_NULL, delim));
}
END_TEST

START_TEST(my_strtok_one_token) {
  char str[32] = "test1/test2/test3/test4";
  char delim[4] = " ,";
  ck_assert_str_eq(my_strtok(str, delim), strtok(str, delim));
  ck_assert_pstr_eq(my_strtok(my_NULL, delim), strtok(my_NULL, delim));
}
END_TEST

START_TEST(my_strtok_empty_delim) {
  char str[32] = "qtw824rgyf8q3";
  char delim[4] = "\0";
  ck_assert_pstr_eq(my_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(my_strtok_empty_str) {
  char str[4] = "";
  char delim[4] = ";,";
  ck_assert_pstr_eq(my_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(my_strtok_empty_str_delim) {
  char str[4] = "";
  char *delim = "\0";
  ck_assert_pstr_eq(my_strtok(str, delim), strtok(str, delim));
}
END_TEST

// Suits

Suite *memchr_suite(void) {
  Suite *s1;
  TCase *tc_core;
  s1 = suite_create("my_memchr");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_memchr_cmp);
  tcase_add_test(tc_core, my_memchr_no_cmp);
  tcase_add_test(tc_core, my_memchr_str_empty);
  tcase_add_test(tc_core, my_memchr_str_less_n);
  tcase_add_test(tc_core, my_memchr_str_null);
  tcase_add_test(tc_core, my_memchr_c_null);
  tcase_add_test(tc_core, my_memchr_c_less_Zero);
  tcase_add_test(tc_core, my_memchr_n_eq_Zero);
  suite_add_tcase(s1, tc_core);
  return s1;
}

Suite *memcmp_suite(void) {
  Suite *s2;
  TCase *tc_core;
  s2 = suite_create("my_memcmp");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_memcmp_part_cmp);
  tcase_add_test(tc_core, my_memcmp_len_less_n);
  tcase_add_test(tc_core, my_memcmp_n_eq_zero);
  tcase_add_test(tc_core, my_memcmp_str1_null);
  tcase_add_test(tc_core, my_memcmp_str2_null);
  tcase_add_test(tc_core, my_memcmp_no_cmp);
  tcase_add_test(tc_core, my_memcmp_full_cmp);
  suite_add_tcase(s2, tc_core);
  return s2;
}

Suite *memcpy_suite(void) {
  Suite *s3;
  TCase *tc_core;
  s3 = suite_create("my_memcpy");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_memcpy_default);
  tcase_add_test(tc_core, my_memcpy_dest_not_empty);
  tcase_add_test(tc_core, my_memcpy_src_empty);
  tcase_add_test(tc_core, my_memcpy_n_eq_zero);
  suite_add_tcase(s3, tc_core);
  return s3;
}

Suite *memset_suite(void) {
  Suite *s4;
  TCase *tc_core;
  s4 = suite_create("my_memset");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_memset_default);
  tcase_add_test(tc_core, my_memset_NULL);
  tcase_add_test(tc_core, my_memset_n_zero);
  tcase_add_test(tc_core, my_memset_c_less_zero);
  tcase_add_test(tc_core, my_memset_str_empty);
  suite_add_tcase(s4, tc_core);
  return s4;
}

Suite *strncat_suite(void) {
  Suite *s5;
  TCase *tc_core;
  s5 = suite_create("my_strncat");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strncat_default);
  tcase_add_test(tc_core, my_strncat_len_less_dest);
  tcase_add_test(tc_core, my_strncat_dest_less_len);
  tcase_add_test(tc_core, my_strncat_empty_dest);
  tcase_add_test(tc_core, my_strncat_empty_src);
  tcase_add_test(tc_core, my_strncat_all_empty);
  suite_add_tcase(s5, tc_core);
  return s5;
}

Suite *strchr_suite(void) {
  Suite *s6;
  TCase *tc_core;
  s6 = suite_create("my_strchr");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strchr_cmp);
  tcase_add_test(tc_core, my_strchr_no_cmp);
  tcase_add_test(tc_core, my_strchr_less_zero);
  tcase_add_test(tc_core, my_strchr_null_symb);
  tcase_add_test(tc_core, my_strchr_empty_str);
  tcase_add_test(tc_core, my_strchr_empty_str_symb);
  suite_add_tcase(s6, tc_core);
  return s6;
}

Suite *strncmp_suite(void) {
  Suite *s7;
  TCase *tc_core;
  s7 = suite_create("my_strncmp");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strncmp_part_cmp);
  tcase_add_test(tc_core, my_strncmp_len_less_n);
  tcase_add_test(tc_core, my_strncmp_n_eq_zero);
  tcase_add_test(tc_core, my_strncmp_str1_null);
  tcase_add_test(tc_core, my_strncmp_str2_null);
  tcase_add_test(tc_core, my_strncmp_no_cmp);
  tcase_add_test(tc_core, my_strncmp_full_cmp);
  suite_add_tcase(s7, tc_core);
  return s7;
}

Suite *strncpy_suite(void) {
  Suite *s8;
  TCase *tc_core;
  s8 = suite_create("my_strncpy");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strncpy_default);
  tcase_add_test(tc_core, my_strncpy_dest_not_empty);
  tcase_add_test(tc_core, my_strncpy_src_empty);
  tcase_add_test(tc_core, my_strncpy_n_eq_zero);
  tcase_add_test(tc_core, my_strncpy_src_shorter);
  suite_add_tcase(s8, tc_core);
  return s8;
}

Suite *strcspn_suite(void) {
  Suite *s9;
  TCase *tc_core;
  s9 = suite_create("my_strcspn");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strcspn_match);
  tcase_add_test(tc_core, my_strcspn_no_match);
  tcase_add_test(tc_core, my_strcspn_str_2_empty);
  tcase_add_test(tc_core, my_strcspn_str_1_empty);
  tcase_add_test(tc_core, my_strcspn_str_1_str_2_empty);
  suite_add_tcase(s9, tc_core);
  return s9;
}

Suite *strerror_suite(void) {
  Suite *s10;
  TCase *tc_core;
  s10 = suite_create("my_strerror");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strerror_test);
  tcase_add_test(tc_core, my_strerror_long_int_neg);
  tcase_add_test(tc_core, my_strerror_long_int_pos);
  suite_add_tcase(s10, tc_core);
  return s10;
}

Suite *strlen_suite(void) {
  Suite *s11;
  TCase *tc_core;
  s11 = suite_create("my_strlen");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strlen_default);
  tcase_add_test(tc_core, my_strlen_null);
  suite_add_tcase(s11, tc_core);
  return s11;
}

Suite *strpbrk_suite(void) {
  Suite *s12;
  TCase *tc_core;
  s12 = suite_create("my_strpbrk");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strpbrk_match);
  tcase_add_test(tc_core, my_strpbrk_no_match);
  tcase_add_test(tc_core, my_strpbrk_str2_empty);
  tcase_add_test(tc_core, my_strpbrk_str1_empty);
  tcase_add_test(tc_core, my_strpbrk_str1_str2_empty);
  suite_add_tcase(s12, tc_core);
  return s12;
}

Suite *strrchr_suite(void) {
  Suite *s13;
  TCase *tc_core;
  s13 = suite_create("my_strrchr");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strrchr_cmp);
  tcase_add_test(tc_core, my_strrchr_no_cmp);
  tcase_add_test(tc_core, my_strrchr_less_zero);
  tcase_add_test(tc_core, my_strrchr_null_symb);
  tcase_add_test(tc_core, my_strrchr_empty_str);
  tcase_add_test(tc_core, my_strrchr_empty_str_symb);
  suite_add_tcase(s13, tc_core);
  return s13;
}

Suite *strstr_suite(void) {
  Suite *s14;
  TCase *tc_core;
  s14 = suite_create("my_strstr");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strstr_match);
  tcase_add_test(tc_core, my_strstr_no_match);
  tcase_add_test(tc_core, my_strstr_needle_empty);
  tcase_add_test(tc_core, my_strstr_haystack_empty);
  tcase_add_test(tc_core, my_strstr_haystack_needle_empty);
  suite_add_tcase(s14, tc_core);
  return s14;
}

Suite *strtok_suite(void) {
  Suite *s15;
  TCase *tc_core;
  s15 = suite_create("my_strtok");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, my_strtok_match);
  tcase_add_test(tc_core, my_strtok_one_token);
  tcase_add_test(tc_core, my_strtok_empty_delim);
  tcase_add_test(tc_core, my_strtok_empty_str);
  tcase_add_test(tc_core, my_strtok_empty_str_delim);
  suite_add_tcase(s15, tc_core);
  return s15;
}

void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int fail = 0;
  case_test(memchr_suite(), &fail);
  case_test(memcmp_suite(), &fail);
  case_test(memcpy_suite(), &fail);
  case_test(memset_suite(), &fail);
  case_test(strncat_suite(), &fail);
  case_test(strchr_suite(), &fail);
  case_test(strncmp_suite(), &fail);
  case_test(strncpy_suite(), &fail);
  case_test(strcspn_suite(), &fail);
  case_test(strerror_suite(), &fail);
  case_test(strlen_suite(), &fail);
  case_test(strpbrk_suite(), &fail);
  case_test(strrchr_suite(), &fail);
  case_test(strstr_suite(), &fail);
  case_test(strtok_suite(), &fail);
  return fail;
}