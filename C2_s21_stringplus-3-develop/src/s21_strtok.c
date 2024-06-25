#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = s21_NULL;
  if (str != s21_NULL) {
    next_token = str;
  } else if (next_token == s21_NULL) {
    return s21_NULL;
  }
  char *start = next_token;
  char *end = start;
  while (*end) {
    const char *d = delim;
    while (*d) {
      if (*end == *d) {
        if (end == start) {
          start++;
          end++;
        } else {
          *end = '\0';
          next_token = end + 1;
          return start;
        }
      } else {
        d++;
      }
    }
    end++;
  }
  next_token = s21_NULL;
  if (end == start) {
    return s21_NULL;
  } else {
    return start;
  }
}