#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (!dest || !src) {
    exit(1);
  }
  s21_size_t i = 0;
  s21_size_t count = 0;
  for (count = s21_strlen(dest); i < n; count++, i++) {
    dest[count] = src[i];
  }
  dest[count] = '\0';
  return (dest);
}
