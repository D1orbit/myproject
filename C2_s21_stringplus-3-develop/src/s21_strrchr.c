#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  if (str == s21_NULL) {
    return s21_NULL;
  }
  const char *ptr = str;
  char *last_occurrence = "";
  while (*ptr != '\0') {
    if (*ptr == c) {
      last_occurrence = (char *)ptr;
    }
    ptr++;
  }
  if (c == '\0') {
    last_occurrence = (char *)ptr;
  }
  if (s21_strlen(last_occurrence) == 0 && c != '\0') {
    return s21_NULL;
  }
  return last_occurrence;
}