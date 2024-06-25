#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  size_t src_len = s21_strlen(src);
  size_t str_len = s21_strlen(str);
  char *result = (char *)malloc(src_len + str_len + 1);
  if (result == s21_NULL || start_index > src_len) {
    return s21_NULL;
  }
  for (size_t i = 0; i < start_index; i++) {
    result[i] = src[i];
  }
  for (size_t i = 0; i < str_len; i++) {
    result[start_index + i] = str[i];
  }
  for (size_t i = start_index; i < src_len; i++) {
    result[str_len + i] = src[i];
  }
  result[src_len + str_len] = '\0';
  return (void *)result;
}