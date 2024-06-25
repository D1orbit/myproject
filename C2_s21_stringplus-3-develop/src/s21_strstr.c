#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (haystack == s21_NULL || needle == s21_NULL) {
    return s21_NULL;
  }
  const char *ptr_h = haystack;
  const char *ptr_n = needle;
  while (*ptr_h != '\0') {
    const char *temp = ptr_h;
    while (*ptr_n != '\0' && *ptr_h == *ptr_n) {
      ptr_h++;
      ptr_n++;
    }
    if (*ptr_n == '\0') {
      return (char *)temp;
    }
    ptr_h = temp + 1;
    ptr_n = needle;
  }
  return s21_NULL;
}
