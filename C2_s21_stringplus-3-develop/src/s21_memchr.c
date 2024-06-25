#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *byte = str;
  for (s21_size_t i = 0; i < n; ++i, ++byte) {
    if (*byte == (unsigned char)c) {
      return ((void *)byte);
    }
  }
  return s21_NULL;
}