#include "../my_string.h"

typedef struct token_struct {
  int left_justify;  // 0 = right(default) 1 = left
  int plus_sign;  // 1 = to write a plus sign before pos number 0 = only minus
                  // for negative
  int space;  // 1 = writes space if there is no negative sign, ignored if '+'
              // is on
  int decimal_point;  //(sharp) 1 = always print a decimal point a, A, e, E, f,
                      // F, g or G
  // for o, x or X specifiers the value is preceeded with 0, 0x or 0X
  // respectively for values different than zero.
  int zeroing;  // pads with '0' instead of ' ', ignore when left-justify is on
  int width;    // if set to -1 (*) needs additional handling
  int precision;   // if set to -1 (*) needs additional handling by default = -2
  char length;     // modifies the TYPE
  char specifier;  // data type
} token;

char *int_to_string(unsigned long long int decimal_number,
                    int base) {  //освободить возвращаемое значение, для
                                 //преобразования в любую систему счисления и
  char tmp[BUFFER_SIZE] = {//и записывает в строку
                           0};
  int j = 0;
  char digits[] = "0123456789abcdef";
  if (decimal_number == 0) {
    tmp[j] = '0';
    j++;
  } else {
    while (decimal_number != 0) {
      tmp[j] = digits[decimal_number % base];
      j++;
      decimal_number /= base;
    }
  }
  char *result = (char *)malloc(j * sizeof(char) + 1);
  char *res_copy = result;
  for (int i = j - 1; i >= 0; i--) {
    *res_copy = tmp[i];
    res_copy++;
  }
  *res_copy = '\0';
  return result;
}

char *build_result_with_spaces(token *unf_token, char *argument,
                               my_size_t spaces_count) {
  my_size_t arg_len = my_strlen(argument);
  char *result = (char *)malloc(arg_len * sizeof(char) + spaces_count + 3);
  char *ptr = result;
  if (unf_token->left_justify == 1) {
    for (my_size_t i = 0; i < arg_len; i++) {
      *ptr = *argument;
      ptr++;
      argument++;
    }
    for (my_size_t i = 0; i < spaces_count; i++) {
      *ptr = ' ';
      ptr++;
    }
    *ptr = '\0';
  }
  if (unf_token->left_justify == 0) {
    for (my_size_t i = 0; i < spaces_count; i++) {
      *ptr = ' ';
      ptr++;
    }
    for (my_size_t i = 0; i < arg_len; i++) {
      *ptr = *argument;
      ptr++;
      argument++;
    }
    *ptr = '\0';
  }
  return result;
}

char *di_specifier_handler(token *unf_token,
                           long int decimal_number) {  //пробел игнорируется при
                                                       //включенном +, # - игнор
  int prec_zeroes = 0, neg_sign = 0, additional_symb = 2;
  char *number = my_NULL;
  char *argument = my_NULL;
  if (decimal_number < 0) {
    neg_sign = 1;
    decimal_number = -decimal_number;
  }
  number = int_to_string(decimal_number, 10);
  if (unf_token->precision > (int)my_strlen(number)) {
    prec_zeroes = unf_token->precision - my_strlen(number);
  }
  if (unf_token->precision == -2 && unf_token->left_justify == 0 &&
      unf_token->zeroing == 1 && unf_token->width != -2) {
    prec_zeroes = unf_token->width - my_strlen(number);
    if (neg_sign || unf_token->space == 1 || unf_token->plus_sign == 1)
      prec_zeroes -= 1;
  }
  if (prec_zeroes < 0) prec_zeroes = 0;
  argument = (char *)malloc(
      (my_strlen(number) + prec_zeroes + additional_symb) * sizeof(char));
  *argument = '\0';
  if (neg_sign) {
    my_strncpy(argument, "-", 2);
  } else if (!neg_sign && unf_token->plus_sign == 1) {
    my_strncpy(argument, "+", 2);
  } else if (!neg_sign && unf_token->space == 1) {
    my_strncpy(argument, " ", 2);
  }
  for (int i = 0; i < prec_zeroes; i++) {
    my_strncat(argument, "0", 2);
  }
  my_strncat(argument, number, my_strlen(number));
  free(number);
  long int spaces_count = 0;
  if (unf_token->width > (long int)my_strlen(argument))
    spaces_count = unf_token->width - my_strlen(argument);
  char *result = build_result_with_spaces(unf_token, argument, spaces_count);
  free(argument);
  return result;
}

char *uoxX_specifier_handler(
    token *unf_token,
    unsigned long int
        decimal_number) {  // 0 флаг игнорируется если установлена точность,
                           // если полученное значение больше точности, точность
                           // игнорируется
  //пробел и плюс игнорируется
  int prec_zeroes = 0;
  char *number = my_NULL;
  char *argument = my_NULL;
  if (my_strchr("pxX", unf_token->specifier))
    number = int_to_string(decimal_number, 16);
  if (my_strchr("u", unf_token->specifier))
    number = int_to_string(decimal_number, 10);
  if (my_strchr("o", unf_token->specifier))
    number = int_to_string(decimal_number, 8);
  if (unf_token->precision > (int)my_strlen(number)) {
    prec_zeroes = unf_token->precision - my_strlen(number);
  }
  if (unf_token->precision == -2 && unf_token->left_justify == 0 &&
      unf_token->zeroing == 1 && unf_token->width != -2) {
    prec_zeroes = unf_token->width - my_strlen(number);
  }
  if (prec_zeroes < 0) prec_zeroes = 0;
  argument =
      (char *)malloc((my_strlen(number) + prec_zeroes + 4) * sizeof(char));
  *argument = '\0';
  if (unf_token->plus_sign == 1 && unf_token->specifier == 'p') {
    my_strncpy(argument, "+", 2);
  } else if (unf_token->space == 1 && unf_token->specifier == 'p') {
    my_strncpy(argument, " ", 2);
  }
  if (unf_token->decimal_point == 1 &&
      my_strchr("pxX", unf_token->specifier) && decimal_number != 0) {
    my_strncat(argument, "0x", 3);
    // prec_zeroes -= 2;
  }
  if (unf_token->decimal_point == 1 && my_strchr("o", unf_token->specifier) &&
      decimal_number != 0 &&
      (unf_token->zeroing == 0 ||
       (unf_token->zeroing == 1 && prec_zeroes == 0)))
    my_strncat(argument, "0", 2);
  for (int i = 0; i < prec_zeroes; i++) {
    my_strncat(argument, "0", 2);
  }
  my_strncat(argument, number, my_strlen(number));
  free(number);
  if (unf_token->specifier == 'X') {
    char *ptr = argument;
    argument = my_to_upper(argument);
    free(ptr);
  }
  long int spaces_count = 0;
  if (unf_token->width > (long int)my_strlen(argument))
    spaces_count = unf_token->width - my_strlen(argument);
  char *result = build_result_with_spaces(unf_token, argument, spaces_count);
  free(argument);
  return result;
}

char *p_specifier_handler(
    token *unf_token,
    unsigned long int
        decimal_number) {  // p игнорирует все флаги кроме left-justify и width
  char *result = my_NULL;
  char *argument = my_NULL;
  if (decimal_number) {
    unf_token->decimal_point = 1;
    result = uoxX_specifier_handler(unf_token, decimal_number);
  } else {
    argument = malloc(6 * sizeof(char));
    my_strncpy(argument, "(nil)", 6);
    int spaces_count = (unf_token->width - my_strlen(argument));
    if (spaces_count < 0) spaces_count = 0;
    result = build_result_with_spaces(unf_token, argument, spaces_count);
  }
  free(argument);
  return result;
}

char *format_to_int(
    const char *format,
    int *n) {  //получает указатель на начало числа в стринг запишет в n число,
               //вернёт указатель на часть формата где оно закончилось
  const char *tmp_ptr = format;
  int number_length = 0;
  *n = 0;
  while (*tmp_ptr >= '0' && *tmp_ptr <= '9') {
    number_length++;
    tmp_ptr++;
  }
  for (int i = 0; i < number_length; i++) {
    *n = *n + (int)pow(10, number_length - 1 - i) * (*format - 48);
    format++;
  }
  return (char *)format;
}

char *parse(const char *format,
            token *unf_token) {  //пока что нет проверок может сегфолтнуть,
                                 //вернёт указатель на формат
  const char *flags_str = "-+ #0";
  const char *length_str = "hlL";
  const char *specifiers_str = "cdieEfgGosuxXpn";
  const char *format_ptr = format;
  format++;  // ofset from %
  // [flags]
  while (my_strchr(flags_str, *format) != my_NULL) {
    if (*format == '-') unf_token->left_justify = 1;
    if (*format == '+') unf_token->plus_sign = 1;
    if (*format == ' ') unf_token->space = 1;
    if (*format == '#') unf_token->decimal_point = 1;
    if (*format == '0') unf_token->zeroing = 1;
    format++;
  }
  //[width]
  if (*format == '*') {
    unf_token->width = -1;
    format++;
  } else if (*format >= '1' && *format <= '9') {
    int a = 0;
    format = format_to_int(format, &a);
    unf_token->width = a;
  }
  //[.precision] если после точки не идёт числа, точность = 0, для дробных по
  //умолчанию = 6, .0012 = .12
  if (*format == '.' && *(format + 1) == '*') {
    unf_token->precision = -1;
    format += 2;
  } else if (*format == '.' && *(format + 1) >= '0' && *(format + 1) <= '9') {
    int b = 0;
    format++;  //сдвинуть с точки
    format = format_to_int(format, &b);
    unf_token->precision = b;
  } else if (*format == '.') {
    unf_token->precision = 0;
    format++;
  }
  //[length]
  if (my_strchr(length_str, *format) != my_NULL) {
    unf_token->length = *format;
    format++;
  }
  // specifier
  if (my_strchr(specifiers_str, *format) != my_NULL) {
    unf_token->specifier = *format;
    format++;
  }
  //если спецификатор не считался, то не смещаем указатель на формат, обработка
  //ошибки будет в deconstruct
  if (unf_token->specifier == 0) format = format_ptr;
  return (char *)format;
}

char *s_specifier_handler(
    token *unf_token,
    char *
        argument) {  //игнорирует все флаги кроме left-justify [width] и
                     //[.precision] , возвращаемую строку нужно будет освободить
  long long int precision = my_strlen(argument);
  char *str_part = (char *)malloc((precision + 1) * sizeof(char));
  if (unf_token->precision < precision && unf_token->precision != -2)
    precision = unf_token->precision;
  my_strncpy(str_part, argument, precision);
  *(str_part + precision) = '\0';
  long long int spaces_count = 0;
  if (unf_token->width > precision) spaces_count = unf_token->width - precision;
  char *result = build_result_with_spaces(unf_token, str_part, spaces_count);
  free(str_part);
  return result;
}

char *prepend_eE_specifier(token *unf_token, char *number, long long int pow) {
  if (unf_token->specifier == 'e') {
    my_strncat(number, "e", 2);
  } else if (unf_token->specifier == 'E') {
    my_strncat(number, "E", 2);
  }
  char *sign = "+";
  if (pow < 0) {
    sign = "-";
    pow = -pow;
  }
  char *tmp = int_to_string(pow, 10);
  if (my_strlen(tmp) == 1) {
    my_strncat(number, sign, 2);
    my_strncat(number, "0", 2);
    my_strncat(number, tmp, 2);
  } else {
    my_strncat(number, sign, 2);
    my_strncat(number, tmp, 2);
  }
  free(tmp);
  return number;
}

char *double_to_int(token *unf_token, long double argument, int *neg_sign,
                    int *delim, int g_flag) {
  long double fractional = 0, tmp_f = 0;
  int leading_frac_zeroes = 0;
  long long unsigned int int_part_d = 0, frac_part_d = 0;
  if (argument < 0.0) {
    *neg_sign = 1;
    argument = -argument;
  }
  fractional = modfl(argument, &tmp_f) * powl(10, unf_token->precision);
  int_part_d = tmp_f;
  if (roundl(fractional) >= pow(10, unf_token->precision)) {
    int_part_d++;
    frac_part_d = roundl(fractional) - powl(10, unf_token->precision);
  } else {
    frac_part_d = roundl(fractional);
  }
  if (g_flag && frac_part_d == 0 && unf_token->decimal_point != 1) {
    unf_token->precision = 0;
  }
  if (unf_token->precision > 0) unf_token->decimal_point = 1;
  char *int_part_str = int_to_string(int_part_d, 10);
  char *frac_part_str = int_to_string(frac_part_d, 10);
  char *ptr = frac_part_str;
  if ((int)my_strlen(frac_part_str) < unf_token->precision)
    leading_frac_zeroes = unf_token->precision - my_strlen(frac_part_str);
  frac_part_str = (char *)malloc(
      (my_strlen(frac_part_str) + leading_frac_zeroes + 2) * sizeof(char));
  *frac_part_str = '\0';
  for (int i = 0; i < leading_frac_zeroes; i++)
    my_strncat(frac_part_str, "0", 1);
  my_strncat(frac_part_str, ptr, my_strlen(ptr));
  free(ptr);
  if (unf_token->specifier == 'f')
    *delim = my_strlen(int_part_str);
  else if (unf_token->specifier == 'e' || unf_token->specifier == 'E')
    *delim = 1;
  char *number = (char *)malloc(
      (my_strlen(int_part_str) + my_strlen(frac_part_str) + 1) *
      sizeof(char));
  *number = '\0';
  my_strncat(number, int_part_str, my_strlen(int_part_str));
  free(int_part_str);
  my_strncat(number, frac_part_str, unf_token->precision);
  free(frac_part_str);
  return number;
}

char *f_specifier_handler(token *unf_token, long double argument, int pow,
                          int g_flag) {
  long int width_zeroes_count = 0;
  int neg_sign = 0, delim = 0;
  char *number = double_to_int(unf_token, argument, &neg_sign, &delim, g_flag);
  if (unf_token->zeroing == 1 && unf_token->left_justify == 0 &&
      unf_token->width != -2) {
    width_zeroes_count = unf_token->width - my_strlen(number);
    if (unf_token->decimal_point == 1) width_zeroes_count--;
    if (unf_token->specifier == 'e' || unf_token->specifier == 'E')
      width_zeroes_count -= 4;
    if (width_zeroes_count < 0) width_zeroes_count = 0;
  }
  char *result = (char *)malloc((my_strlen(number) + width_zeroes_count + 10) *
                                sizeof(char));
  *result = '\0';
  char *tmp_ptr = result;
  if (neg_sign) {
    my_strncpy(result, "-", 2);
    width_zeroes_count--;
    delim += 1;
  } else if (!neg_sign && unf_token->plus_sign == 1) {
    my_strncpy(result, "+", 2);
    width_zeroes_count--;
    delim += 1;
  } else if (!neg_sign && unf_token->space == 1) {
    my_strncpy(result, " ", 2);
    width_zeroes_count--;
    delim += 1;
  }
  if (width_zeroes_count < 0) width_zeroes_count = 0;
  for (long int i = 0; i < width_zeroes_count; i++) {
    my_strncat(result, "0", 2);
  }
  my_strncat(result, number, my_strlen(number));
  if (unf_token->specifier == 'e' || unf_token->specifier == 'E')
    prepend_eE_specifier(unf_token, result, pow);
  if (unf_token->decimal_point == 1) {
    result = my_insert(result, ".", delim + width_zeroes_count);
    free(tmp_ptr);
    tmp_ptr = result;
  }
  my_size_t spaces_count = 0;
  if (unf_token->width > (int)my_strlen(result))
    spaces_count = unf_token->width - my_strlen(result);
  result = build_result_with_spaces(unf_token, result, spaces_count);
  free(tmp_ptr);
  free(number);
  return result;
}

long double normalize(long double argument, int *pow) {
  *pow = 0;
  if (fabsl(argument) >= 10.0)
    while (fabsl(argument) > 10.0) {
      argument /= 10;
      *pow = *pow + 1;
    }
  else if ((int)fabsl(argument) - fabsl(argument))
    while ((int)fabsl(argument) == 0) {
      argument *= 10;
      *pow = *pow - 1;
    }
  return argument;
}

char *feEgG_specifier_handler(token *unf_token, long double argument) {
  char *result = my_NULL;
  int pow = 0;
  if (unf_token->precision < 0) unf_token->precision = 6;
  if (unf_token->specifier == 'f') {
    result = f_specifier_handler(unf_token, argument, 0, 0);
  }
  if (unf_token->specifier == 'e' || unf_token->specifier == 'E') {
    argument = normalize(argument, &pow);
    result = f_specifier_handler(unf_token, argument, pow, 0);
  }
  if (unf_token->specifier == 'g' || unf_token->specifier == 'G') {
    normalize(argument, &pow);
    if (unf_token->precision == 0) unf_token->precision = 1;
    if (pow >= -4 && pow < unf_token->precision) {
      unf_token->specifier = 'f';
      unf_token->precision = unf_token->precision - 1 - pow;
      result = f_specifier_handler(unf_token, argument, 0, 1);
    } else {
      if (unf_token->specifier == 'g') unf_token->specifier = 'e';
      if (unf_token->specifier == 'G') unf_token->specifier = 'E';
      unf_token->precision = unf_token->precision - 1;
      argument = normalize(argument, &pow);
      result = f_specifier_handler(unf_token, argument, pow, 1);
    }
  }
  return result;
}

char *c_specifier_handler(
    token *unf_token,
    int argument) {  //игнорирует все флаги кроме left-justify, [width]
  my_size_t spaces_count = 0;
  if (unf_token->width > 0) {
    spaces_count = unf_token->width - 1;
  }
  char *char_tmp = (char *)malloc(2 * sizeof(char));
  *char_tmp = (char)argument;
  *(char_tmp + 1) = '\0';
  char *result = build_result_with_spaces(unf_token, char_tmp, spaces_count);
  free(char_tmp);
  return result;
}

char *add_to_output_string(
    char *str, char *result,
    my_size_t
        *printed_char_count) {  //добавляет result к str, возвращает смещённый
                                //указатель на стр, увеличивает счётчик
  *printed_char_count = *printed_char_count + my_strlen(result);
  my_size_t res_len = my_strlen(result);
  for (my_size_t i = 0; i < res_len; i++) {
    *str = *result;
    str++;
    result++;
  }
  return str;
}

char *filter_unsupported_wchars(
    wchar_t *w_argument) {  //освободить возвращаемую строку
  my_size_t wchar_len = 0;
  wchar_t *ptr = w_argument;
  while (*ptr != 0) {
    wchar_len++;
    ptr++;
  }
  char *argument = (char *)malloc(wchar_len * sizeof(char) + 1);
  char *arg_ptr = argument;
  while (*w_argument != L'\0') {
    *argument = (char)*w_argument;
    argument++;
    w_argument++;
  }
  *argument = '\0';
  return arg_ptr;
}

char *nan_result(token *unf_token, long double argument) {
  char *result = my_NULL;
  if (argument == INFINITY) {
    int spaces_count = unf_token->width - 3;
    if (spaces_count < 0) spaces_count = 0;
    result = build_result_with_spaces(unf_token, "inf", spaces_count);
  } else if (argument == -INFINITY) {
    int spaces_count = unf_token->width - 4;
    if (spaces_count < 0) spaces_count = 0;
    result = build_result_with_spaces(unf_token, "-inf", spaces_count);
  } else if (isnan(argument)) {
    int spaces_count = unf_token->width - 3;
    if (spaces_count < 0) spaces_count = 0;
    result = build_result_with_spaces(unf_token, "nan", spaces_count);
  }
  if (unf_token->specifier == 'E' || unf_token->specifier == 'G') {
    char *ptr = result;
    result = my_to_upper(result);
    free(ptr);
  }

  return result;
}

char *logic_handler(
    char *str, va_list input_args, token *unf_token,
    my_size_t *printed_char_count) {  //удобнее будет здесь же
                                       //вызывать функцию обработки
  //формата и записи форматированной строки в стр
  if (unf_token->width == -1) {
    unf_token->width = va_arg(input_args, int);
    if (unf_token->width < 0) {
      unf_token->width = -unf_token->width;
      unf_token->left_justify = 1;
    }
  }
  if (unf_token->precision == -1) {
    unf_token->precision = va_arg(input_args, int);
    if (unf_token->precision < 0) unf_token->precision = -2;
  }

  if (unf_token->specifier == 'd' || unf_token->specifier == 'i') {  // di
    long int argument = 0;
    if (unf_token->length == 0) argument = (int)va_arg(input_args, int);
    if (unf_token->length == 'h') argument = (short int)va_arg(input_args, int);
    if (unf_token->length == 'l') argument = va_arg(input_args, long int);
    char *result = di_specifier_handler(unf_token, argument);
    str = add_to_output_string(str, result, printed_char_count);
    free(result);
  }
  if (my_strchr("uoxX", unf_token->specifier) != my_NULL) {  // uoxX
    unsigned long int argument = 0;
    if (unf_token->length == 0)
      argument = (unsigned int)va_arg(input_args, unsigned int);
    if (unf_token->length == 'h')
      argument = (unsigned short int)va_arg(input_args, unsigned int);
    if (unf_token->length == 'l')
      argument = va_arg(input_args, unsigned long int);
    char *result = uoxX_specifier_handler(unf_token, argument);
    str = add_to_output_string(str, result, printed_char_count);
    free(result);
  }
  if (my_strchr("feEgG", unf_token->specifier) != my_NULL) {  // feEgG
    long double argument = 0;
    char *result = my_NULL;
    if (unf_token->length == 0 || unf_token->length == 'h' ||
        unf_token->length == 'l') {
      argument = va_arg(input_args, double);
    }
    if (unf_token->length == 'L') {
      argument = va_arg(input_args, long double);
    }
    if (isfinite((double)argument)) {
      result = feEgG_specifier_handler(unf_token, argument);
    } else
      result = nan_result(unf_token, argument);
    str = add_to_output_string(str, result, printed_char_count);
    free(result);
  }
  if (unf_token->specifier == 'c') {  // c
    if (unf_token->length == 0) {
      int argument = 0;
      argument = va_arg(input_args, int);
      char *result = c_specifier_handler(unf_token, argument);
      str = add_to_output_string(str, result, printed_char_count);
      free(result);
    }
    if (unf_token->length == 'l') {
      wint_t argument = 0;
      argument = va_arg(input_args, wint_t);
      char *result = c_specifier_handler(unf_token, argument);
      str = add_to_output_string(str, result, printed_char_count);
      free(result);
    }
  }
  if (unf_token->specifier == 's') {
    if (unf_token->length == 0) {
      char *argument = 0;
      argument = va_arg(input_args, char *);
      if (argument == my_NULL) argument = "";
      char *result = s_specifier_handler(unf_token, argument);
      str = add_to_output_string(str, result, printed_char_count);
      free(result);
    }
    if (unf_token->length == 'l') {
      int *w_argument = 0;
      w_argument = va_arg(input_args, wchar_t *);
      if (w_argument == my_NULL) w_argument = L"";
      char *argument = filter_unsupported_wchars(w_argument);
      char *result = s_specifier_handler(unf_token, (char *)argument);
      str = add_to_output_string(str, result, printed_char_count);
      free(argument);
      free(result);
    }
  }
  if (unf_token->specifier == 'n') {  // n
    if (unf_token->length == 0) {
      int *argument = 0;
      argument = va_arg(input_args, int *);
      *argument = (int)*printed_char_count;
    }
    if (unf_token->length == 'h') {
      short int *argument = 0;
      argument = (short int *)va_arg(input_args, int *);
      *argument = (short int)*printed_char_count;
    }
    if (unf_token->length == 'l') {
      long int *argument = 0;
      argument = va_arg(input_args, long int *);
      *argument = (long int)*printed_char_count;
    }
  }
  if (unf_token->specifier == 'p') {
    unsigned long int argument = 0;
    argument = va_arg(input_args, unsigned long int);
    char *result = p_specifier_handler(unf_token, argument);
    str = add_to_output_string(str, result, printed_char_count);
    free(result);
  }
  return str;
}

my_size_t format_deconstruct(
    char *str, const char *format,
    va_list input_args) {  //%[flags][width][.precision][length]specifier
  my_size_t printed_char_count = 0;
  while (*format) {
    if (*format != '%') {
      *str = *format;
      printed_char_count++;
      str++;
      format++;
    } else if (*format == '%' && *(format + 1) == '%') {
      *str = *format;
      printed_char_count++;
      str++;
      format += 2;
    } else if (*format == '%' && *(format + 1) != '%') {
      token unf_token = {0,  0,  0, 0, 0,
                         -2, -2, 0, 0};  // -2 по дефолту, это значит что
                                         // никакого значения не считано
      format = parse(format, &unf_token);
      if (unf_token.specifier != 0) {
        str = logic_handler(str, input_args, &unf_token, &printed_char_count);
      } else {  //если токен не считался
        format++;
        str = add_to_output_string(
            str, "%",
            &printed_char_count);  //в случае ошибки, смещаем с процента, и
                                   //процент записываем в результат вручеую
      }
    }
  }
  *str = '\0';
  return printed_char_count;
}

int my_sprintf(char *str, const char *format,
                ...) {  //добавить проверку что формат не НУЛЛ и стр не НУЛЛ
  unsigned long count = -1;
  if (str != my_NULL && format != my_NULL) {
    va_list input_args;
    va_start(input_args, format);
    count = format_deconstruct(str, format, input_args);
    va_end(input_args);
  }
  return count;
}