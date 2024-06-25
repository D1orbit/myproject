#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *src = str;
  for (s21_size_t i = 0; i < n; ++i, ++src) {
    *src = (unsigned char)c;
  }
  return (str);
}