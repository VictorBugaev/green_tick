#include "../my_string.h"

#define BASE_8 "01234567"
#define BASE_10 "0123456789"
#define BASE_16 "0123456789AaBbCcDdEeFf"
#define BASE_FLOAT "0123456789.eE-+"

#define WIDTH_DEFAULT -1
#define LENGTH_DEFAULT ' '
#define STR_SIZE 300

struct token {
  int width;
  char length;
  char specifier;
  int is_skip;
  int write_symb;
};

void my_write_count_sum(va_list args, struct token *current_token) {
  if (!current_token->is_skip && current_token->length == 'h')
    *(va_arg(args, unsigned short *)) =
        (unsigned short)(current_token->write_symb);
  else if (!current_token->is_skip && current_token->length == 'l')
    *(va_arg(args, unsigned long *)) =
        (unsigned long)(current_token->write_symb);
  else if (!current_token->is_skip)
    *(va_arg(args, unsigned int *)) = (unsigned int)(current_token->write_symb);
}

int my_get_digits(const char **str, char *alphabet, char *dest,
                   int max_width) {
  int find_digit = 0;
  int i = 0;
  if (max_width == -1) max_width = 2048;
  char first = **str;
  char second = *(++(*str));
  if (first == '0' && my_strchr(alphabet, 'a') != my_NULL &&
      (second == 'x' || second == 'X'))
    (*str)++;
  else
    (*str)--;
  while (i < max_width && my_strchr(alphabet, **str) != my_NULL &&
         **str != '\0') {
    dest[i] = **str;
    find_digit = 1;
    (*str)++;
    i++;
  }
  if (find_digit) dest[i] = '\0';
  return find_digit;
}

int my_write_to_float_s(va_list args, struct token *current_token,
                         const char **str) {
  while (**str == ' ') (*str)++;

  if (!current_token || !args) return 0;

  int flag = 0, sign = 1;
  int width = current_token->width;
  if (width == -1) width = 2048;
  char result[width + 1];
  if (**str == '-') {
    sign = -1;
    (*str)++;
    if (width != -1) width--;
  }

  int len = 0;
  while ((**str >= 'a' && **str <= 'z') || (**str >= 'A' && **str <= 'Z')) {
    result[len++] = *(*str)++;
  }

  result[len] = '\0';
  char *up_res = my_to_upper(result);
  if (my_strncmp(up_res, "INF", 3) == 0 ||
      my_strncmp(up_res, "NAN", 3) == 0) {
    flag = 1;
  }
  free(up_res);

  if (!flag) {
    // Если не INF, inf, NAN, или nan, то возвращаем указатель назад и
    // преобразуем дальше строку в число
    (*str) -= len;
    flag = my_get_digits(str, BASE_FLOAT, result, width);
  }

  if (flag) {
    current_token->write_symb += my_strlen(result);
    if (!current_token->is_skip && current_token->length == 'l') {
      *(va_arg(args, double *)) = (double)strtold(result, NULL) * sign;
    } else if (!current_token->is_skip && current_token->length == 'L') {
      *(va_arg(args, long double *)) = strtold(result, NULL) * sign;
    } else if (!current_token->is_skip) {
      *(va_arg(args, float *)) = (float)strtold(result, NULL) * sign;
    } else {
      flag = 0;
    }
  }
  return flag;
}

unsigned long int my_convert_16_to_10(char *result) {
  int sign = 1;
  if (*result == '-') {
    result++;
    sign = -1;
  }
  int str_len = my_strlen(result) - 1;
  unsigned long int sum = 0;
  while (str_len >= 0) {
    char current_char = *result;

    if (current_char >= 'a' && current_char <= 'f')
      sum += (10 + current_char - 'a') * pow(16, str_len);
    else if (current_char >= 'A' && current_char <= 'F')
      sum += (10 + current_char - 'A') * pow(16, str_len);
    else
      sum += (current_char - '0') * pow(16, str_len);
    result++;
    str_len--;
  }
  return sum * sign;
}

unsigned int my_convert_8_to_10(char *result) {
  int sign = 1;
  if (*result == '-') {
    result++;
    sign = -1;
  }
  unsigned int sum = 0;
  while (*result == '0') {
    result++;
  }
  while (*result != '\0') {
    char current_char = *result;
    if (current_char >= '0' && current_char <= '7') {
      sum = sum * 8 + (current_char - '0');
    } else {
      break;
    }
    result++;
  }
  return sum * sign;
}

int my_put_sign_int(char *result, struct token *current_token, va_list args,
                     int sign) {
  int flag = 0;

  if (*result == '\0') return 0;

  long long long_value;
  current_token->write_symb += my_strlen(result);

  if (current_token->specifier == 'd' || current_token->specifier == 'i')
    long_value = atoll(result) * sign;
  else
    return 0;

  if (current_token->length == 'h') {
    *(va_arg(args, short *)) = (short)long_value;
    flag = 1;
  } else if (current_token->length == 'l') {
    *(va_arg(args, long *)) = long_value;
    flag = 1;
  } else {
    *(va_arg(args, int *)) = (int)long_value;
    flag = 1;
  }
  return flag;
}

int put_unsign_int_in_value(char *result, struct token *current_token,
                            va_list args, int sign) {
  int flag = 0;

  if (*result == '\0') return 0;

  long long long_value;
  current_token->write_symb += my_strlen(result);

  if (current_token->specifier == 'x' || current_token->specifier == 'X')
    long_value = my_convert_16_to_10(result) * sign;
  else if (current_token->specifier == 'o')
    long_value = my_convert_8_to_10(result);
  else if (current_token->specifier == 'u')
    long_value = atoll(result) * sign;
  else
    return 0;

  if (current_token->length == 'h') {
    *(va_arg(args, unsigned short *)) = (unsigned short)long_value;
    flag = 1;
  } else if (current_token->length == 'l') {
    *(va_arg(args, unsigned long *)) = (unsigned)long_value;
    flag = 1;
  } else {
    *(va_arg(args, unsigned int *)) = (unsigned int)long_value;
    flag = 1;
  }
  return flag;
}

int my_write_to_int_s(va_list args, struct token *current_token,
                       const char **str) {
  while (**str == ' ') (*str)++;
  int flag = 0;
  int alphabet = 0;
  if (current_token->specifier == 'i' || current_token->specifier == 'd' ||
      current_token->specifier == 'u')
    alphabet = 10;
  else if (current_token->specifier == 'x' || current_token->specifier == 'X' ||
           current_token->specifier == 'p')
    alphabet = 16;
  else if (current_token->specifier == 'o')
    alphabet = 8;

  int width = current_token->width;
  int sign = 1;
  char result[64] = {0};
  if (**str == '-') {
    (*str)++;
    if (current_token->width != -1) width--;
    current_token->write_symb++;
    sign = -1;
  } else if (**str == '+') {
    (*str)++;
    if (current_token->width != -1) width--;
    current_token->write_symb++;
  }

  if (**str == '0' &&
      (current_token->specifier == 'i' || current_token->specifier == 'p')) {
    char next_char = *(++(*str));
    if ((current_token->specifier == 'i' || current_token->specifier == 'p') &&
        (next_char == 'X' || next_char == 'x')) {
      (*str)++;
      current_token->specifier = 'X';
      alphabet = 16;
      if (current_token->width != -1) width--;
    } else if (current_token->specifier == 'i') {
      (*str)--;
      current_token->specifier = 'o';
      alphabet = 8;
    }

    current_token->write_symb++;
    if (width != -1) width--;
    if (current_token->specifier == 'o') result[0] = '0';
  }
  if (alphabet == 10)
    flag = my_get_digits(str, BASE_10, result, width);
  else if (alphabet == 8)
    flag = my_get_digits(str, BASE_8, result, width);
  else
    flag = my_get_digits(str, BASE_16, result, width);
  if (flag && !current_token->is_skip)
    if (current_token->specifier == 'd' || current_token->specifier == 'i')
      flag = my_put_sign_int(result, current_token, args, sign);
    else
      flag = put_unsign_int_in_value(result, current_token, args, sign);
  else
    flag = 0;
  return flag;
}

int my_put_char_in_var(va_list args, struct token *current_token,
                        char *result) {
  int flag = 0;
  int index = 0;
  wchar_t *arg_str_w;
  char *arg_str_s;
  if (current_token->length == 'l' && !current_token->is_skip)
    arg_str_w = va_arg(args, wchar_t *);
  else if (!current_token->is_skip)
    arg_str_s = va_arg(args, char *);
  while (result[index] != '\0') {
    if (!current_token->is_skip && current_token->length == 'l') {
      *arg_str_w = result[index];
      arg_str_w++;
      flag = 1;
    } else if (!current_token->is_skip && current_token->length != 'l') {
      *arg_str_s = result[index];
      arg_str_s++;
      flag = 1;
    }
    index++;
  }
  if (current_token->specifier == 's' && current_token->length == 'l' &&
      !current_token->is_skip)
    *arg_str_w = '\0';
  else if (current_token->specifier == 's' && current_token->length != 'l' &&
           !current_token->is_skip)
    *arg_str_s = '\0';
  return flag;
}

int my_write_char_in_var(va_list args, struct token *current_token,
                          const char **str) {
  if (**str == '\0') return 0;
  if (current_token->width == WIDTH_DEFAULT) current_token->width = 1;
  int flag = 1, index = 0;
  char result[STR_SIZE] = {0};
  while (**str != '\0' && current_token->width > 0) {
    result[index] = **str;
    (*str)++;
    index++;
    current_token->width--;
    current_token->write_symb++;
  }
  flag = my_put_char_in_var(args, current_token, result);
  return flag;
}
int my_write_str_in_var(va_list args, struct token *current_token,
                         const char **str) {
  int flag = 0;
  while ((**str == ' ' || **str == '\n' || **str == '\t') &&
         current_token->specifier == 's')
    (*str)++;
  int index = 0;
  char result[STR_SIZE + 1];
  while (**str != '\0' &&
         (current_token->width || current_token->width == -1)) {
    if (**str == '\n' || **str == '\t' || **str == ' ') break;
    result[index] = **str;
    (*str)++;
    index++;
    if (current_token->width != -1) current_token->width--;
  }
  result[index] = '\0';
  if (my_strlen(result) >= 1)
    flag = my_put_char_in_var(args, current_token, result);
  current_token->write_symb += my_strlen(result);
  return flag;
}

int my_parsing(struct token *current_token, const char **format) {
  int flag = 1;
  while (flag && *format) {
    switch (**format) {
      case '*':
        current_token->is_skip = 1;
        break;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        char result[20] = {0};
        my_get_digits(format, BASE_10, result, sizeof(result));
        current_token->width = atoi(result);
        (*format)--;
        break;
      case 'h':
      case 'l':
      case 'L':
        current_token->length = (**format);
        break;
      default:
        if (my_strchr("cdieEfgGosuxXpn", **format) != my_NULL)
          current_token->specifier = **format;
        if (**format != '%') flag = 0;
        break;
    }
    (*format)++;
  }
  return flag;
}

int my_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  if (*str == '\0' || my_strchr(format, '%') == my_NULL) {
    va_end(args);
    return 0;
  }
  int count_write_var = 0;
  int count_symb = 0;
  while (*format != '\0') {
    struct token current_token = {WIDTH_DEFAULT, LENGTH_DEFAULT, ' ', 0,
                                  count_symb};
    if (*format == '%') {
      format++;
      if (*format == '%' && *str == '%')  //когда идет %% в формате
      {
        format++;
        str++;
        continue;
      }

      int flag = my_parsing(&current_token, &format);
      if (current_token.specifier == ' ') break;

      if (current_token.specifier == 's')
        flag = my_write_str_in_var(args, &current_token, &str);

      else if (current_token.specifier == 'c')
        flag = my_write_char_in_var(args, &current_token, &str);

      else if (current_token.specifier == 'n')
        my_write_count_sum(args, &current_token);

      else if (my_strchr("xXpoiud", current_token.specifier) != my_NULL)
        flag = my_write_to_int_s(args, &current_token, &str);

      else if (my_strchr("eEfFgG", current_token.specifier) != my_NULL)
        flag = my_write_to_float_s(args, &current_token, &str);
      if (flag) count_write_var++;
      if (!flag && !current_token.is_skip && count_write_var == 0 &&
          str[0] != *str)
        return -1;
    } else if (*format == *str) {
      format++;
      str++;
      current_token.write_symb++;
    } else
      return count_write_var;
    count_symb = current_token.write_symb;
  }
  return count_write_var;
}
