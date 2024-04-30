#ifndef MY_STRING_H
#define MY_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define my_NULL ((void *)0)
#define BUFFER_SIZE 4096
typedef long unsigned int my_size_t;

//Реализация функций stdio.h
int my_sscanf(const char *str, const char *format, ...);
int my_sprintf(char *str, const char *format, ...);

//Реализация функций string.h
void *my_memchr(const void *str, int c, my_size_t n);
int my_memcmp(const void *str1, const void *str2, my_size_t n);
void *my_memcpy(void *dest, const void *src, my_size_t n);
void *my_memset(void *str, int c, my_size_t n);
char *my_strncat(char *dest, const char *src, my_size_t n);
char *my_strcat(char *dest, const char *src);
char *my_strchr(const char *str, int c);
int my_strncmp(const char *str1, const char *str2, my_size_t n);
char *my_strncpy(char *dest, const char *src, my_size_t n);
my_size_t my_strcspn(const char *str1, const char *str2);
char *my_strerror(int errnum);
my_size_t my_strlen(const char *str);
char *my_strpbrk(const char *str1, const char *str2);
char *my_strrchr(const char *str, int c);
char *my_strstr(const char *haystack, const char *needle);
char *my_strtok(char *str, const char *delim);

//Реализация специальных функций обработки строк
void *my_to_upper(const char *str);
void *my_to_lower(const char *str);
void *my_insert(const char *src, const char *str, my_size_t start_index);
void *my_trim(const char *src, const char *trim_chars);

#endif