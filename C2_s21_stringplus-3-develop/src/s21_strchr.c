#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  if (str == s21_NULL) {
    return s21_NULL;
  }
  char *byte = "\0";
  for (; *str != '\0'; str++) {
    if (*str == c) {
      byte = (char *)str;
      break;
    }
  }
  if (s21_strlen(byte) == 0 && c != '\0') {
    return s21_NULL;
  }
  return byte;
}