#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t k = 0;
  int flag = 0;
  for (s21_size_t first_symbol = 0; *(str1 + first_symbol); ++first_symbol) {
    for (s21_size_t i = 0; *(str2 + i); ++i) {
      if (*(str1 + first_symbol) == *(str2 + i)) {
        flag = 1;
        break;
      }
    }
    if (flag == 1) {
      k = first_symbol;
      break;
    }
    if (!(*(str1 + first_symbol + 1))) {
      k = first_symbol + 1;
    }
  }
  return k;
}