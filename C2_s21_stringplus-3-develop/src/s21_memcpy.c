#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *copy = (char *)src;
  char *insert = (char *)dest;
  if (!dest || !src) {
    exit(1);
  }
  for (s21_size_t i = 0; i < n; ++i) {
    insert[i] = copy[i];
  }
  return (insert);
}