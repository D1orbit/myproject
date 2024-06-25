#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define s21_size_t unsigned long long
#define s21_NULL ((void *)0)

struct s21_sprintf {
  int c;
  int d;
  int f;
  int s;
  int u;
  int wight;
  int percent;
  int other;
  int plus;
};

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strchr(const char *str, int c);
char *s21_strcpy(char *dest, const char *src);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strncpy(char *destination, const char *source, s21_size_t num);
char *s21_strerror(int errorNumber);
char *s21_to1_string_int(int x, char *str);
int s21_numcount_int(int x);
char *s21_strcat(char *dest, const char *src);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strcpy(char *dest, const char *src);
void s21_to_string_int(int x, s21_size_t *size, char *num);
int print_unsigned(unsigned num, char *str);
void s21_parse_format(const char *format, struct s21_sprintf *flag);
int s21_sprintf(char *buf, const char *format, ...);
void reverse(char s[]);
void reversedot(char s[], int j);
void ftoa(double n, char *massive);
int s21_intnumber(const char *number, int count_number,
                  struct s21_sprintf *flag);

#endif
