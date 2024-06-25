#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int flag = 0;
  const unsigned char *byte1 = str1;
  const unsigned char *byte2 = str2;
  for (s21_size_t i = 0; i < n; ++i, ++byte1, ++byte2) {
    if (*byte1 != *byte2) {
      flag = *byte1 - *byte2;
      break;
    }
  }
  return (flag);
}