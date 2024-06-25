#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  if (str1 == s21_NULL || str2 == s21_NULL) {
    return s21_NULL;
  }
  const char *ptr1 = str1;
  while (*ptr1 != '\0') {
    const char *ptr2 = str2;
    while (*ptr2 != '\0') {
      if (*ptr1 == *ptr2) {
        return (char *)ptr1;
      }
      ptr2++;
    }
    ptr1++;
  }
  return s21_NULL;
}