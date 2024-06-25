#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if ((src == s21_NULL && trim_chars == s21_NULL) ||
      (src == s21_NULL && trim_chars != s21_NULL)) {
    return s21_NULL;
  }
  s21_size_t src_len = s21_strlen(src);
  s21_size_t begin = 0;
  s21_size_t end = src_len - 1;

  while (src[begin] != '\0' && s21_strchr(trim_chars, src[begin]) != s21_NULL) {
    begin++;
  }
  while (src[end] != '\0' && s21_strchr(trim_chars, src[end]) != s21_NULL) {
    end--;
  }
  s21_size_t result_len = end - begin + 1;
  char *result = (char *)malloc(result_len + 1);
  if (result == s21_NULL) {
    return s21_NULL;
  }
  for (s21_size_t i = 0; i < result_len; i++) {
    result[i] = src[begin + i];
  }
  result[result_len] = '\0';
  return result;
}
